#include "mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*wall_img;
	void	*bg_img;
	void	*heart_img;
	void	*exit_img;
	void	*player_img;
	int		img_width;
	int		img_height;
	// Dummy map for example
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
}				t_vars;

void	*load_image(t_vars *vars, char *path)
{
	return (mlx_xpm_file_to_image(vars->mlx, path, &vars->img_width, &vars->img_height));
}

int	mlx_pitw(t_vars *g, void *img, int *i)
{
	return (mlx_put_image_to_window(g->mlx, g->win, img, i[2], i[3]));
}

void	render_map(t_vars *g)
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

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307) // ESC
	{
		printf("ESC pressed, closing...\n");
		mlx_loop_end(vars->mlx);
	}
	else
		printf("Keycode: %d\n", keycode);
	return (0);
}

int	handle_close(t_vars *g)
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
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	exit(0);
	return (0);
}

int	main(void)
{
	t_vars	g;

	g.img_width = 32;
	g.img_height = 32;
	g.mlx = mlx_init();
	if (!g.mlx)
		return (1);
	g.win = mlx_new_window(g.mlx, 640, 480, "Hello world!");
	if (!g.win)
		return (1);

	g.wall_img = load_image(&g, "./xpm/wall.xpm");
	g.bg_img = load_image(&g, "./xpm/background.xpm");
	g.heart_img = load_image(&g, "./xpm/heart.xpm");
	g.exit_img = load_image(&g, "./xpm/exit.xpm");
	g.player_img = load_image(&g, "./xpm/player.xpm");

	// Dummy example map
	char *map_data[] = {
		"11111",
		"10C01",
		"10E01",
		"10001",
		"11111",
		NULL
	};
	g.map = map_data;
	g.map_width = 5;
	g.map_height = 5;
	g.player_x = 2;
	g.player_y = 2;

	render_map(&g);

	mlx_key_hook(g.win, key_hook, &g);
	mlx_hook(g.win, 17, 0, handle_close, &g);

	mlx_loop(g.mlx);
	handle_close(&g);
	return (0);
}
