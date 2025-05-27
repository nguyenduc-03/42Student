/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:10:33 by ducnguye          #+#    #+#             */
/*   Updated: 2025/05/19 17:10:33 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "check_map.h"

static	void	*load_image(t_game *g, const char *p)
{
	int		w;
	int		h;
	void	*img;

	w = g->img_width;
	h = g->img_height;
	img = mlx_xpm_file_to_image(g->mlx, (char *)p, &w, &h);
	if (!img || w != g->img_width || h != g->img_height)
		print_error("Error: Image load failed");
	return (img);
}

void	load_images(t_game *g)
{
	g->wall_img = load_image(g, "./xpm/wall.xpm");
	g->bg_img = load_image(g, "./xpm/background.xpm");
	g->heart_img = load_image(g, "./xpm/heart.xpm");
	g->exit_img = load_image(g, "./xpm/exit.xpm");
	g->player_img = load_image(g, "./xpm/player.xpm");
}

void	render_map(t_game *g)
{
	int	i[4];

	i[0] = 0;
	while (i[0] < g->map_height)
	{
		i[1] = 0;
		while (i[1] < g->map_width)
		{
			i[2] = i[1] * g->img_width;
			i[3] = i[0] * g->img_height;
			if (g->map[i[0]][i[1]] == '1')
				mlx_pitw(g, g->wall_img, i);
			else if (g->map[i[0]][i[1]] == '0')
				mlx_pitw(g, g->bg_img, i);
			else if (g->map[i[0]][i[1]] == 'C')
				mlx_pitw(g, g->heart_img, i);
			else if (g->map[i[0]][i[1]] == 'E')
				mlx_pitw(g, g->exit_img, i);
			i[1]++;
		}
		i[0]++;
	}
	i[2] = g->player_x * g->img_width;
	i[3] = g->player_y * g->img_height;
	mlx_pitw(g, g->player_img, i);
}

int	handle_close(t_game *g, t_map *m)
{
	int	i;

	mlx_destroy_image(g->mlx, g->wall_img);
	mlx_destroy_image(g->mlx, g->bg_img);
	mlx_destroy_image(g->mlx, g->heart_img);
	mlx_destroy_image(g->mlx, g->exit_img);
	mlx_destroy_image(g->mlx, g->player_img);
	mlx_destroy_window(g->mlx, g->win);
	i = 0;
	while (i < g->map_height)
	{
		free(g->map[i]);
		i++;
	}
	free(g->map);
	if (m)
		free_map(m);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	g->mlx = NULL;
	exit(0);
	return (0);
}

int	mlx_pitw(t_game *g, void *img, int *i)
{
	return (mlx_put_image_to_window(g->mlx, g->win, img, i[2], i[3]));
}
