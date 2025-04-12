#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h> // for key symbol constants like XK_Escape

typedef struct s_vars {
	void	*mlx;
	void	*win;
	void	*background_img;
	void	*character_img;
	int		bg_width;
	int		bg_height;
	int		char_width;
	int		char_height;
	int		char_x;
	int		char_y;
}				t_vars;

int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == XK_a)
		vars->char_x -= 10;
	else if (keycode == XK_s)
		vars->char_y += 10;
	else if (keycode == XK_d)
		vars->char_x += 10;
	else if (keycode == XK_w)
		vars->char_y -= 10;

	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->character_img, vars->char_x, vars->char_y);

	return (0);
}

int	handle_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (1);

	vars.win = mlx_new_window(vars.mlx, 800, 800, "Find the keys");
	if (!vars.win)
		return (1);

	vars.background_img = mlx_xpm_file_to_image(vars.mlx, "./background.xpm", &vars.bg_width, &vars.bg_height);
	if (!vars.background_img)
	{
		write(2, "Error: Failed to load background.xpm\n", 37);
		exit(1);
	}

	vars.character_img = mlx_xpm_file_to_image(vars.mlx, "./character.xpm", &vars.char_width, &vars.char_height);
	if (!vars.character_img)
	{
		write(2, "Error: Failed to load character.xpm\n", 36);
		exit(1);
	}

	vars.char_x = 0;
	vars.char_y = 0;

	mlx_put_image_to_window(vars.mlx, vars.win, vars.background_img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.character_img, vars.char_x, vars.char_y);

	mlx_hook(vars.win, DestroyNotify, 0, (int (*)(void *))handle_close, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, (int (*)(int, void *))handle_keypress, &vars);

	mlx_loop(vars.mlx);
	return (0);
}
