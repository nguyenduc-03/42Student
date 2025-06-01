/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_clean_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:02:26 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/31 23:00:04 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clean_and_return(t_list **lst, t_game *game, int fd, int status)
{
	if (lst && *lst)
		ft_lstclear(lst, &free);
	if (game)
	{
		if (game->map.colls_coord)
			ft_coord_lstclear(&game->map.colls_coord);
	}
	if (fd > 2)
		close(fd);
	return (status);
}

void	clean_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	exit_game(t_game *game)
{
	if (game->image.collect)
		mlx_destroy_image(game->mlx_ptr, game->image.collect);
	if (game->image.player)
		mlx_destroy_image(game->mlx_ptr, game->image.player);
	if (game->image.exit)
		mlx_destroy_image(game->mlx_ptr, game->image.exit);
	if (game->image.floor)
		mlx_destroy_image(game->mlx_ptr, game->image.floor);
	if (game->image.wall)
		mlx_destroy_image(game->mlx_ptr, game->image.wall);
	clean_grid(game->grid_map);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	clean_and_return(NULL, game, 0, 0);
	free(game->mlx_ptr);
	exit(0);
	return (0);
}
