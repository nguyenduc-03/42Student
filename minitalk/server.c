#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h> 
//#define _POSIX_C_SOURCE 200809L


volatile sig_atomic_t bit_count = 0;
volatile sig_atomic_t current_char = 0;

void handle_signal(int sig, siginfo_t *info, void *context) {
    (void)context;
    if (sig == SIGUSR1) {
        current_char |= (0 << bit_count);
    } else if (sig == SIGUSR2) {
        current_char |= (1 << bit_count);
    }

    bit_count++;

    if (bit_count == 8) {
        if (current_char == 0) {
            printf("\n");
            kill(info->si_pid, SIGUSR1); // Acknowledge end of string
        } else {
            printf("%c", current_char);
            fflush(stdout);
        }
        bit_count = 0;
        current_char = 0;
    }
}

int main(void) {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handle_signal;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    pid_t pid = getpid();
    printf("Server PID: %d\n", pid);

    while (1) {
        pause(); // Wait for incoming signals
    }

    return 0;
}