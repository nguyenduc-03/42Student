/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:48:29 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/27 17:53:45 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <game.h>

void	free_images_and_window(t_game *g)
{
	if (g->wall_img)
		mlx_destroy_image(g->mlx, g->wall_img);
	if (g->bg_img)
		mlx_destroy_image(g->mlx, g->bg_img);
	if (g->heart_img)
		mlx_destroy_image(g->mlx, g->heart_img);
	if (g->exit_img)
		mlx_destroy_image(g->mlx, g->exit_img);
	if (g->player_img)
		mlx_destroy_image(g->mlx, g->player_img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
}

void	free_map_and_exit(t_game *g)
{
	int	i;

	if (g->map)
	{
		i = 0;
		while (i < g->map_height)
		{
			free(g->map[i]);
			i++;
		}
		free(g->map);
	}
	exit(0);
}
