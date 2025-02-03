#include <signal.h>
#include <unistd.h>
#include <stdio.h>

// We use volatile sig_atomic_t to safely handle changes across signals
volatile sig_atomic_t current_char = 0;
volatile sig_atomic_t bit_count = 0;

// Signal handler that processes the incoming SIGUSR1 and SIGUSR2 signals
void handle_signal(int signum)
{
	if (signum == SIGUSR1) {
		current_char |= (0 << bit_count);
	} else if (signum == SIGUSR2) {
		current_char |= (1 << bit_count);
	}
	bit_count++;

	if (bit_count == 8) {  // We have received a full character
		char c = (char)current_char;  // Convert safely to a character type
		write(1, &c, 1);
		// Reset for the next character
		current_char = 0;
		bit_count = 0;
	}
}

int main(void)
{
	struct sigaction sa;

	// Set up the sigaction struct to handle signals
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	printf("Server PID: %d\n", getpid());

	// Set up the signal handlers
	if (sigaction(SIGUSR1, &sa, NULL) == -1) {
		perror("Error setting up SIGUSR1 handler");
		return 1;
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1) {
		perror("Error setting up SIGUSR2 handler");
		return 1;
	}

	// Continuously wait for signals
	while (1) {
		pause();  // Wait for a signal to be delivered
	}

	return 0;
}