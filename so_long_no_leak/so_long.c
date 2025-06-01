/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:26:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/31 23:00:33 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_game(t_game *game, int w, int h)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr, w * SIZE, h * SIZE, "42");
	game->moves = 0;
	if (!game->win_ptr)
	{
		free(game->mlx_ptr);
		return ;
	}
	if (!load_images(&game->image, game->mlx_ptr))
		exit_game(game);
	mount_game(game);
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &handle_key, game);
	mlx_hook(game->win_ptr, 17, StructureNotifyMask, &exit_game, game);
	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_list	*lst;
	t_game	game;

	if (argc == 2)
	{
		lst = NULL;
		ft_memset(&game, 0, sizeof(t_game));
		game.grid_map = get_grid_map(&lst, &game, &fd, argv[1]);
		if (!game.grid_map)
			return (clean_and_return(&lst, &game, fd, 1));
		clean_and_return(&lst, &game, fd, 0);
		start_game(&game, game.map.width, game.map.height);
		clean_grid(game.grid_map);
		return (clean_and_return(NULL, &game, 0, 1));
	}
	return (0);
}
