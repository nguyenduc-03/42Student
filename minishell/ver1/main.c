#include "cell.h"
#include "color.h"
volatile sig_atomic_t g_status = 0; // ONLY global (authorized)



static void sigint_handler(int signo) {
    (void)signo;
    g_status = 130; // bash: SIGINT -> 130 when it interrupts a foreground job
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void sigquit_handler(int signo) {
    (void)signo;
    // In interactive prompt with no running child, bash ignores SIGQUIT
    // We just redraw prompt
    rl_on_new_line();
    rl_redisplay();
}



char *join_path(const char *dir, const char *cmd) {
    size_t a = strlen(dir), b = strlen(cmd);
    char *out = malloc(a + 1 + b + 1);
    if (!out) return NULL;
    memcpy(out, dir, a);
    out[a] = '/';
    memcpy(out + a + 1, cmd, b + 1);
    return out;
}


static void setup_signals_interactive(void) {
    struct sigaction sa_int = {0}, sa_quit = {0};
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_handler = sigint_handler;
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_handler = sigquit_handler;
    sa_quit.sa_flags = SA_RESTART;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

static void setup_signals_in_child(void) {
    // Restore default so child gets proper signals
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

int is_whitespace_only(const char *s)
{
    for (; *s; ++s) if (*s!=' ' && *s!='\t' && *s!='\n') return 0;
    return 1;
}

int is_builtin(const char *cmd) {
    return cmd && (!strcmp(cmd,"exit") || !strcmp(cmd,"cd"));
}


static int bi_exit(char **argv) {
    int code = g_status;
    if (argv[1]) code = atoi(argv[1]); // you’ll add numeric checks
    printf("exit\n");
    clear_history();
    exit(code);
}

static int bi_cd(char **argv) {
    const char *target = argv[1] ? argv[1] : getenv("HOME");
    if (!target) { perror("cd"); return 1; }
    if (chdir(target) != 0) { perror("cd"); return 1; }
    return 0;
}
int run_builtin(char **argv) {
    if (!argv || !argv[0]) return 0;
    if (!strcmp(argv[0],"exit")) return bi_exit(argv);
    if (!strcmp(argv[0],"cd"))   return bi_cd(argv);
    return 0;
}

static void free_argv(char **argv) {
    if (!argv) return;
    for (size_t i=0; argv[i]; ++i) free(argv[i]);
    free(argv);
}



char *resolve_cmd(const char *cmd) {
    if (strchr(cmd, '/')) {
        if (access(cmd, X_OK) == 0) return strdup(cmd);
        return NULL;
    }
    const char *path = getenv("PATH");
    if (!path) return NULL;
    char *dup = strdup(path);
    if (!dup) return NULL;
    char *saveptr = NULL, *dir = strtok_r(dup, ":", &saveptr);
    while (dir) {
        char *full = join_path(dir, cmd);
        if (full && access(full, X_OK) == 0) { free(dup); return full; }
        free(full);
        dir = strtok_r(NULL, ":", &saveptr);
    }
    free(dup);
    return NULL;
}

static int exec_external(char **argv, char **envp) {
    static const char *colors[] = {"\033[1;31m", "\033[1;33m", "\033[1;32m", "\033[1;36m", "\033[1;35m"};
    int color_index = rand() % 5; // random color for this command
    char *path = resolve_cmd(argv[0]);
    if (!path) { 
        fprintf(stderr, "%s: command not found\n", argv[0]); 
        return 127; 
    }

    pid_t pid = fork();
    if (pid < 0) { 
        perror("fork"); 
        free(path); 
        return 1; 
    }

    if (pid == 0) { // child
        setup_signals_in_child();
        printf("%s", colors[color_index]); // set color for command output
        fflush(stdout);
        execve(path, argv, envp);
        perror("execve"); // only reached on error
        _exit(126);
    }

    free(path);

    int status = 0;
    if (waitpid(pid, &status, 0) < 0) perror("waitpid");

    printf("\033[0m"); // reset color after command finishes
    fflush(stdout);

    if (WIFEXITED(status)) return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        if (sig == SIGINT) write(1, "\n", 1);
        else if (sig == SIGQUIT) write(1, "Quit: 3\n", 8);
        return 128 + sig;
    }

    return 1;
}


char *generate_prompt(void)
{
    const char *colors[] = {RED, YEL, GRN, CYN, MAG};
    const char *text = "shell$>";
    int len = strlen(text);
    char *prompt = malloc(len * 10); // enough space for colors
    if (!prompt) return NULL;
    prompt[0] = '\0';

    for (int i = 0; i < len; i++) {
        int color_index = rand() % NUM_COLORS;
        strcat(prompt, colors[color_index]);
        strncat(prompt, &text[i], 1);
    }
    strcat(prompt, RST);
    return prompt;
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    setup_signals_interactive();
    rl_catch_signals = 0 ;
    char *line;
    


    srand(time(NULL));

    //REPL
    //READ -> Eva -> Print/Exe -> Loop
    while(1)
    {
        char *promt = generate_prompt();
        line = readline(promt);
        free(promt);
        //1)use readline

        if(line == NULL)
        {
            write(1, "exit\n",5);
            break;
        }
        //1.2) add to history
        if(!is_whitespace_only(line))
            add_history(line);

        //system(line);
         char **av = ft_split(line,' ');
        if (av && av[0]) {
            if (is_builtin(av[0])) {
                g_status = run_builtin(av);
            } else {
                g_status = exec_external(av, envp);
            }
        }
        free_argv(av);
        free(line);
        //2) get tokens gettok -> lexing -> parsing EVA

        //3) Exec
    

    }
    clear_history();
    return EXIT_SUCCESS;
}