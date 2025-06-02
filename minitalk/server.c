/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:06:21 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/02 16:06:33 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/* 
 * Global struct variable to store the message dynamically.
 */
static t_message	g_message = {NULL, 0};

/* 
 * Appends received byte to the dynamically allocated message buffer.
 */
void	append_byte(void)
{
	char	*temp;
	char	c;

	temp = NULL;
	c = (char)g_message.current_char;
	if (g_message.msg)
	{
		temp = ft_strjoin(g_message.msg, &c);
		free(g_message.msg);
	}
	else
		temp = ft_strdup(&c);
	if (!temp)
		exit(EXIT_FAILURE);
	g_message.msg = temp;
}

/* 
 * Handles end of message: prints message and resets memory.
 */
void	process_character(void)
{
	if (g_message.current_char == '\0')
	{
		if (g_message.msg)
			ft_putendl_fd(g_message.msg, 1);
		else
			ft_putendl_fd("\n", 1);
		free(g_message.msg);
		g_message.msg = NULL;
	}
	else
		append_byte();
	g_message.current_char = 0;
}

/* 
 * Signal handler to reconstruct the message bit by bit.
 * Uses `sigaction` with `SA_SIGINFO` to get sender PID and send confirmation.
 */
void	handle_signal(int signal, siginfo_t *info, void *context)
{
	static int	current_bit = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_message.current_char = (g_message.current_char << 1) | 1;
	else if (signal == SIGUSR2)
		g_message.current_char = (g_message.current_char << 1);
	current_bit++;
	if (current_bit == 8)
	{
		process_character();
		current_bit = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

/* 
 * Initializes the server and waits for signals indefinitely.
 * Uses `sigaction` with `SA_SIGINFO` to allow access to sender PID.
 */
int	main(void)
{
	struct sigaction	sig_config;

	ft_putstr_fd("\nServer running with PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sig_config.sa_sigaction = handle_signal;
	sig_config.sa_flags = SA_SIGINFO;
	sigemptyset(&sig_config.sa_mask);
	sigaction(SIGUSR1, &sig_config, NULL);
	sigaction(SIGUSR2, &sig_config, NULL);
	while (1)
		pause();
	return (0);
}
