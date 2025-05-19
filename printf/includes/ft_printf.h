/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   $TM_FILENAME                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguyen@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:00:00 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/17 12:01:32 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>

// Function prototypes
int	ft_printf(const char *format, ...);
int	ft_putchar_fd(char c, int fd);
int	ft_putstr_fd(const char *s, int fd);
int	ft_putnbr_fd(int n, int fd);
int	ft_putnbr_base_fd(unsigned int n, const char *base, int fd);
int	ft_putptr_fd(void *ptr, int fd);
#endif