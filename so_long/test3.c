#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

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

// Function to handle key press for character movement
int	handle_keypress(int keycode, t_vars *vars)
{
	if (keycode == 53) // Escape key to close window
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 0) // 'A' key
		vars->char_x -= 10;
	else if (keycode == 1) // 'S' key
		vars->char_y += 10;
	else if (keycode == 2) // 'D' key
		vars->char_x += 10;
	else if (keycode == 13) // 'W' key
		vars->char_y -= 10;

	// Redraw the images
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->background_img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->character_img, vars->char_x, vars->char_y);

	return (0);
}

int	main(void)
{
	t_vars	vars;

	// Initialize the MiniLibX instance
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 600, "XPM Example");

	// Load background image (XPM format)
	vars.background_img = mlx_xpm_file_to_image(vars.mlx, "./backround.xpm", &vars.bg_width, &vars.bg_height);
	if (!vars.background_img)
	{
		write(2, "Error: Failed to load background.xpm\n", 37);
		exit(1);
	}

	// Load character image (XPM format)
	vars.character_img = mlx_xpm_file_to_image(vars.mlx, "character.xpm", &vars.char_width, &vars.char_height);
	if (!vars.character_img)
	{
		write(2, "Error: Failed to load character.xpm\n", 36);
		exit(1);
	}

	// Initialize character position
	vars.char_x = 200;
	vars.char_y = 200;

	// Display the images
	mlx_put_image_to_window(vars.mlx, vars.win, vars.background_img, 0, 0);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.character_img, vars.char_x, vars.char_y);

	// Hook key press event
	mlx_key_hook(vars.win, handle_keypress, &vars);

	// Enter the event loop
	mlx_loop(vars.mlx);

	return (0);
}
