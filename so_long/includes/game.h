#ifndef GAME_H
# define GAME_H
# include <unistd.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <mlx.h>

typedef struct s_game {
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	void	*wall_img;
	void	*bg_img;
	void	*heart_img;
	void	*exit_img;
	void	*player_img;
	int		img_width;
	int		img_height;
	int		player_x;
	int		player_y;
	int		heart;
	int		moves;
}	t_game;

void	render_map(t_game *game);
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);
//void	start_game(char **map, int width, int height, int p_x, int p_y, int hearts);
void	start_game(char **map, int i[5]);


void	load_images(t_game *g);
int		mlx_pitw(t_game *g, void *img, int *i);

#endif