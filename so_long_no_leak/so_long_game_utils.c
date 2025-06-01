/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 21:59:30 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/31 22:59:44 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_img(t_game *game, void *img_ptr, int x, int y)
{
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img_ptr, x, y);
}

void	mount_game(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (game->grid_map[i])
	{
		j = 0;
		while (game->grid_map[i][j])
		{
			if (game->grid_map[i][j] == '1')
				render_img(game, game->image.wall, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == '0')
				render_img(game, game->image.floor, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'P')
				render_img(game, game->image.player, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'E')
				render_img(game, game->image.exit, j * SIZE, i * SIZE);
			else if (game->grid_map[i][j] == 'C')
				render_img(game, game->image.collect, j * SIZE, i * SIZE);
			j++;
		}
		i++;
	}
}

int	load_images(t_image *image, void *mlx_ptr)
{
	int	x;
	int	y;

	image->collect = mlx_xpm_file_to_image(mlx_ptr, "textures/c.xpm", &x, &y);
	image->floor = mlx_xpm_file_to_image(mlx_ptr, "textures/0.xpm", &x, &y);
	image->player = mlx_xpm_file_to_image(mlx_ptr, "textures/p.xpm", &x, &y);
	image->wall = mlx_xpm_file_to_image(mlx_ptr, "textures/1.xpm", &x, &y);
	image->exit = mlx_xpm_file_to_image(mlx_ptr, "textures/e.xpm", &x, &y);
	if (!image->collect || !image->floor || !image->player
		|| !image->wall || !image->exit)
		return (send_err("Can't load images.", 0));
	return (1);
}

void	move_player(int x, int y, t_game *game)
{
	int	old_x;
	int	old_y;

	old_x = game->map.start_coord.x;
	old_y = game->map.start_coord.y;
	if (game->grid_map[y][x] != '1' && game->grid_map[y][x] != 'E')
	{
		if (game->grid_map[y][x] == 'C')
		{
			game->grid_map[y][x] = '0';
			game->score++;
		}
		game->moves++;
		ft_printf("Moves: %i\n", game->moves);
		render_img(game, game->image.floor, old_x * SIZE, old_y * SIZE);
		render_img(game, game->image.player, x * SIZE, y * SIZE);
		game->map.start_coord.x = x;
		game->map.start_coord.y = y;
	}
	else if (game->grid_map[y][x] == 'E' && game->score == game->map.colls)
		exit_game(game);
}

int	handle_key(int keysym, t_game *game)
{
	if (keysym == XK_w || keysym == XK_Up)
		move_player(game->map.start_coord.x, game->map.start_coord.y - 1, game);
	if (keysym == XK_s || keysym == XK_Down)
		move_player(game->map.start_coord.x, game->map.start_coord.y + 1, game);
	if (keysym == XK_a || keysym == XK_Left)
		move_player(game->map.start_coord.x - 1, game->map.start_coord.y, game);
	if (keysym == XK_d || keysym == XK_Right)
		move_player(game->map.start_coord.x + 1, game->map.start_coord.y, game);
	return (0);
}
