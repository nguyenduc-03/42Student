/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 15:50:41 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/02 16:05:27 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
 * Global variable to track server acknowledgment.
 */
static int	g_reply = 0;

/*
	* Signal handler to update the global
	reply variable when a SIGUSR1 is received.
 */
void	signal_reception(int signal)
{
	if (signal == SIGUSR1)
		g_reply = 1;
}

/*
 * Function to send a single bit to the server via a signal.
 * It sends SIGUSR1 if the bit is 1 and SIGUSR2 if the bit is 0.
 * The function uses a small delay (usleep) and waits for confirmation
 * from the server before continuing.
 */
void	send_bit_to_server(pid_t server_pid, int bit_value)
{
	if (bit_value == 1)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	usleep(10000);
	while (!g_reply)
		pause();
	g_reply = 0;
}

/*
 * Function to send the entire message to the server.
 * It sends the message byte by byte and bit by bit, including multi-byte
 * characters forUnicode. After sending the message, it sends a final 8
 * bits (all 0s) to mark the end of the message.
 */
void	send_message_to_server(pid_t server_pid, const char *message)
{
	size_t			i;
	int				bit_position;
	unsigned char	current_byte;

	i = 0;
	while (message[i] != '\0')
	{
		current_byte = (unsigned char)message[i];
		bit_position = 7;
		while (bit_position >= 0)
		{
			send_bit_to_server(server_pid, (current_byte >> bit_position) & 1);
			bit_position--;
		}
		i++;
	}
	bit_position = 7;
	while (bit_position >= 0)
	{
		send_bit_to_server(server_pid, 0);
		bit_position--;
	}
}

/*
 * Main function to execute the client.
 * It takes the server PID and the message to be sent as command-line arguments.
 * It then sends the message to the server.
 */
int	main(int argc, char **argv)
{
	pid_t		server_pid;
	const char	*message;

	if (argc != 3)
	{
		ft_putendl_fd("Usage: ./client server_PID \"message\"", 1);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putendl_fd("Error: Invalid PID.", 1);
		return (1);
	}
	signal(SIGUSR1, signal_reception);
	message = argv[2];
	send_message_to_server(server_pid, message);
	return (0);
}
