/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_error_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 23:47:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/31 23:03:05 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	send_err(char *err, int status)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(err, 2);
	return (status);
}

int	is_valid_char(char c)
{
	char	*valid_chars;

	valid_chars = "10EPC";
	if (!ft_strchr(valid_chars, c))
		return (0);
	return (1);
}

int	is_valid_path(int *fd, char *filename)
{
	char	*extension;

	*fd = open(filename, O_RDONLY);
	if (*fd == -1)
	{
		ft_putendl_fd(FILE_NOT_EXIST, 2);
		return (0);
	}
	extension = ft_strrchr(filename, '.');
	if (ft_strcmp(extension, ".ber"))
	{
		ft_putendl_fd(FILE_EXT_ERR, 2);
		return (0);
	}
	return (1);
}
