#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void send_char(int pid, char c)
{
	for (int i = 0; i < 8; i++)
	{
		int bit = (c >> i) & 1;
		if (bit == 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		
		usleep(100); // Sleep briefly to allow signal processing
	}
}
	
int main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(2, "Usage: ./client [server_pid] [string]\n", 39);
		return 1;
	}

	int server_pid = atoi(argv[1]);
	char *string = argv[2];

	while (*string)
		send_char(server_pid, *string++);

	return 0;
}