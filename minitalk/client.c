

#include <stdio.h>

#include <sys/types.h> 
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void send_signal_char(pid_t server_pid, char c) {
    for (int i = 0; i < 8; i++) {
        if (c & (1 << i)) {
            kill(server_pid, SIGUSR2);
        } else {
            kill(server_pid, SIGUSR1);
        }
        sleep(10); // Short sleep to ensure the server processes signals
    }
}

void handle_ack(int sig) {
    (void)sig;
    printf("Message received by server.\n");
    exit(0);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_pid> <message>\n", argv[0]);
        return 1;
    }

    pid_t server_pid = atoi(argv[1]);
    char *message = argv[2];

    // Setup handler for acknowledgment signal
    signal(SIGUSR1, handle_ack);

    // Send each character in the message
    for (size_t i = 0; i <= strlen(message); i++) {
        send_signal_char(server_pid, message[i]);
    }

    // Wait for acknowledgment from server
    pause();

    return 0;
}