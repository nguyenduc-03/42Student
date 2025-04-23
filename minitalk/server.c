#include "minitalk.h"

static void	ft_putpid(pid_t n)
{
	char	c;

	if (n > 9)
	{
		ft_putpid((n / 10));
		ft_putpid((n % 10));
	}
	else
	{
		c = 48 + n;
		write(1, &c, 1);
	}
}

static void	signal_handler(int signal)
{
	static char	chr;
	static int	i;

	i++;
	if (signal == SIGUSR1)
		chr = chr | 1;
	if (i == 8)
	{
		write(1, &chr, 1);
		i = 0;
		chr = 0;
	}
	chr = chr << 1;
}

int	main(void)
{
	pid_t	server_id;

	server_id = getpid();
	write(1, "PID :",5);
	ft_putpid(server_id);
	write(1, "\n",1);
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	while (1)
	{
		pause();
	}
	return (0);
}