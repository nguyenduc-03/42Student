/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ducnguye <ducnguye@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:31:17 by edfreder          #+#    #+#             */
/*   Updated: 2025/06/01 04:20:01 by ducnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# define SIZE 64
# define FILE_NOT_EXIST "File does not exist."
# define FILE_EXT_ERR "Non compatible map extension."
# define MAP_CHR_ERR "Map must have 1 exit, 1 start and at least 1 collectable."
# define MAP_INV_CHR_ERR "Map has an invalid character."
# define MAP_WALL_ERR "Map not surronded by walls."
# define MAP_SIZE_ERR "File .ber must have at least 3 lines."
# define MAP_COLLECT_ERR "Invalid map. Collectables not reachable."
# define MAP_EXIT_ERR "Invalid map. Exit not reachable."

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "X11/keysym.h"
# include "X11/X.h"
#include <fcntl.h>

typedef struct s_coord
{
	int				x;
	int				y;
	struct s_coord	*next;
}	t_coord;

typedef struct s_map
{
	int		width;
	int		height;
	int		start;
	int		exit;
	int		colls;
	t_coord	start_coord;
	t_coord	exit_coord;
	t_coord	*colls_coord;
}	t_map;

typedef struct s_image
{
	void	*collect;
	void	*floor;
	void	*player;
	void	*wall;
	void	*exit;
}	t_image;

typedef struct s_game
{
	t_map	map;
	t_image	image;
	char	**grid_map;
	int		score;
	int		moves;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

/* Errors */
int		send_err(char *err, int status);
int		is_valid_path(int *fd, char *filename);
int		is_valid_char(char c);
/* Utils */
char	**create_grid(t_list *lst, int height);
int		save_map_info(char *line, int line_index, t_map *map);
int		build_map(t_list **lst, int fd);
char	**get_grid_map(t_list **lst, t_game *game, int *fd, char *filename);
/* Coord utils */
void	coord_addback(t_coord **head, t_coord *new);
int		save_coord(t_map *map, int x, int y, char c);
void	ft_coord_lstclear(t_coord **coord_lst);
int		coord_check(t_coord *coord, char **grid_map, char c);
/* Map */
int		check_rectangule(int *line_len, int *curr_len);
int		check_plays(char **grid, t_map *map);
int		check_map(char **grid, t_map *map);
void	mark_plays(char **grid_map, int x, int y, char mark);
/* Clean */
void	clean_grid(char **grid);
int		clean_and_return(t_list **lst, t_game *game, int fd, int status);
int		exit_game(t_game *game);
/* Game */
void	start_game(t_game *game, int width, int height);
int		handle_key(int keysym, t_game *game);
void	move_player(int x, int y, t_game *game);
int		load_images(t_image *image, void *mlx_ptr);
void	mount_game(t_game *game);

#endif