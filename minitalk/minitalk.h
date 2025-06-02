/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:06:29 by ducnguye          #+#    #+#             */
/*   Updated: 2025/06/02 16:06:30 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define BUFFER 90000

/* 
 * Struct to manage dynamic message storage.
 * - `char *msg`: Holds the dynamically allocated message.
 * - `int current_char`: Stores the character being reconstructed from bits.
 */
typedef struct s_message
{
	char	*msg;
	int		current_char;
}	t_message;

#endif
