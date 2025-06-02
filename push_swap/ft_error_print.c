/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_print.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 22:47:21 by ducnguye    +#+    #+#             */
/*   Updated: 2025/05/17 22:47:21 by ducnguye    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Here an error message is being printed out
void	ft_error(void)
{
	write (2, "Error\n", 6);
	exit(1);
}
