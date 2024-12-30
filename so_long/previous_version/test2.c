#include <mlx.h>
#include <stdlib.h>
#include <X11/X.h> // Required for KeyPress and event masks

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

// Function to handle the closing of the window
int	handle_close(int keycode, t_vars *vars)
{
	if (keycode == 65307) // 65307 is the keycode for ESC
	{
		mlx_destroy_window(vars->mlx, vars->win); // Close the window
		exit(0); // Exit the program
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;

	// Initialize MiniLibX and create a new window
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");

	// Hook the handle_close function to KeyPress events
	mlx_hook(vars.win, KeyPress, KeyPressMask, handle_close, &vars);

	// Start the event loop
	mlx_loop(vars.mlx);
}
