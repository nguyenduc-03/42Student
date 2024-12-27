#include <mlx.h>
#include <unistd.h>

int main(void)
{
	void	*mlx;
	void	*mlx_win;

	// Initialize MiniLibX
	mlx = mlx_init();
	if (!mlx)
	{
		write(2, "Error: Failed to initialize MiniLibX\n", 37);
		return (1);
	}

	// Create a new window
	mlx_win = mlx_new_window(mlx, 800, 600, "Hello, MiniLibX!");
	if (!mlx_win)
	{
		write(2, "Error: Failed to create window\n", 31);
		return (1);
	}

	// Enter the MiniLibX event loop
	mlx_loop(mlx);
	return (0);
}
