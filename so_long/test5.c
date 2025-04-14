#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>	// For printf
#include <X11/X.h>	// For KeyPress, KeyPressMask, DestroyNotify
#include "check_map.h"

// Assuming check_map.h provides these functions
char **read_map(const char *filename, int *width, int *height);
void validate_map(char **map, int width, int height);

typedef struct s_game {
	void	*mlx;
	void	*win;
	char	**map;
	int	 map_width;
	int	 map_height;
	void	*wall_img;
	void	*background_img;
	void	*heart_img;
	void	*exit_img;
	void	*player_img;
	int	 img_width;
	int	 img_height;
	int	 player_x;
	int	 player_y;
	int	 heart;
	int	 moves;
} t_game;

// Function to render the map and player
void render_map(t_game *game)
{
	mlx_clear_window(game->mlx, game->win); // Clear to avoid artifacts
	for (int i = 0; i < game->map_height; i++)
	{
		for (int j = 0; j < game->map_width; j++)
		{
			int x = j * game->img_width;
			int y = i * game->img_height;
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img, x, y);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->background_img, x, y);
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->heart_img, x, y);
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit_img, x, y);
		}
	}
	// Draw the player at its current position
	int player_x_pos = game->player_x * game->img_width;
	int player_y_pos = game->player_y * game->img_height;
	mlx_put_image_to_window(game->mlx, game->win, game->player_img, player_x_pos, player_y_pos);
}

// Function to handle key presses
int handle_keypress(int keycode, t_game *game)
{
	if (keycode == 65307) // ESC key
	{
		mlx_destroy_window(game->mlx, game->win);
		exit(0);
	}

	int new_x = game->player_x;
	int new_y = game->player_y;
	if (keycode == 119) // W key
		new_y--;
	else if (keycode == 115) // S key
		new_y++;
	else if (keycode == 97) // A key
		new_x--;
	else if (keycode == 100) // D key
		new_x++;
	else
		return (0); // Ignore other keys

	// Check boundaries
	if (new_x < 0 || new_x >= game->map_width || new_y < 0 || new_y >= game->map_height)
		return (0);

	char next = game->map[new_y][new_x];
	if (next == '1') // Wall
		return (0);

	if (next == '0' || next == 'C') // background or heart
	{
		if (next == 'C')
		{
			game->map[new_y][new_x] = '0'; // Remove heart
			game->heart--;
		}
		game->player_x = new_x;
		game->player_y = new_y;
		game->moves++;
		printf("Moves: %d\n", game->moves);
		render_map(game);
	}
	else if (next == 'E') // Exit
	{
		if (game->heart == 0)
		{
			printf("You win! Moves: %d\n", game->moves);
			mlx_destroy_window(game->mlx, game->win);
			exit(0);
		}
		// Can't move onto exit yet if heart remain
	}
	return (0);
}

// Function to handle window close
int handle_close(t_game *game)
{
	mlx_destroy_image(game->mlx, game->wall_img);
	mlx_destroy_image(game->mlx, game->background_img);
	mlx_destroy_image(game->mlx, game->heart_img);
	mlx_destroy_image(game->mlx, game->exit_img);
	mlx_destroy_image(game->mlx, game->player_img);
	mlx_destroy_window(game->mlx, game->win);
	for (int i = 0; i < game->map_height; i++)
		free(game->map[i]);
	free(game->map);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 29);
		exit(1);
	}

	// Read and validate the map
	int width, height;
	char **map = read_map(argv[1], &width, &height);
	if (!map)
	{
		write(2, "Error: Failed to read map\n", 26);
		exit(1);
	}
	validate_map(map, width, height);

	// Find player position and count heart
	int player_x = -1, player_y = -1;
	int heart = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i][j] == 'P')
			{
				player_x = j;
				player_y = i;
				map[i][j] = '0'; // Replace 'P' with background
			}
			else if (map[i][j] == 'C')
				heart++;
		}
	}
	if (player_x == -1 || player_y == -1)
	{
		write(2, "Error: No player start position found\n", 38);
		exit(1);
	}

	// Initialize game struct
	t_game game;
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		write(2, "Error: Failed to initialize MiniLibX\n", 38);
		exit(1);
	}

	// Set tile size and window dimensions
	int tile_size = 32; // Assuming all images are 32x32 pixels
	game.img_width = tile_size;
	game.img_height = tile_size;
	game.map_width = width;  // Set before window creation
	game.map_height = height;
	printf("Map: %dx%d, Tile: %dx%d, Window: %dx%d\n", 
		   game.map_width, game.map_height, 
		   tile_size, tile_size, 
		   game.map_width * tile_size, game.map_height * tile_size);
	game.win = mlx_new_window(game.mlx, 
							  game.map_width * tile_size, 
							  game.map_height * tile_size, 
							  "so_long");
	if (!game.win)
	{
		write(2, "Error: Failed to create window\n", 31);
		exit(1);
	}

	// Load images (adjust paths based on your xpm/ directory)
	int img_width = tile_size;
	int img_height = tile_size;
	game.wall_img = mlx_xpm_file_to_image(game.mlx, "./xpm/wall.xpm", &img_width, &img_height);
	if (!game.wall_img || img_width != tile_size || img_height != tile_size)
	{
		write(2, "Error: Failed to load wall.xpm or wrong size\n", 45);
		exit(1);
	}
	img_width = tile_size;
	img_height = tile_size;
	game.background_img = mlx_xpm_file_to_image(game.mlx, "./xpm/background.xpm", &img_width, &img_height);
	if (!game.background_img || img_width != tile_size || img_height != tile_size)
	{
		write(2, "Error: Failed to load background.xpm or wrong size\n", 50);
		exit(1);
	}
	img_width = tile_size;
	img_height = tile_size;
	game.heart_img = mlx_xpm_file_to_image(game.mlx, "./xpm/heart.xpm", &img_width, &img_height);
	if (!game.heart_img || img_width != tile_size || img_height != tile_size)
	{
		write(2, "Error: Failed to load heart.xpm or wrong size\n", 46);
		exit(1);
	}
	img_width = tile_size;
	img_height = tile_size;
	game.exit_img = mlx_xpm_file_to_image(game.mlx, "./xpm/exit.xpm", &img_width, &img_height);
	if (!game.exit_img || img_width != tile_size || img_height != tile_size)
	{
		write(2, "Error: Failed to load exit.xpm or wrong size\n", 44);
		exit(1);
	}
	img_width = tile_size;
	img_height = tile_size;
	game.player_img = mlx_xpm_file_to_image(game.mlx, "./xpm/player.xpm", &img_width, &img_height);
	if (!game.player_img || img_width != tile_size || img_height != tile_size)
	{
		write(2, "Error: Failed to load player.xpm or wrong size\n", 47);
		exit(1);
	}

	// Set game state
	game.map = map;
	game.player_x = player_x;
	game.player_y = player_y;
	game.heart = heart;
	game.moves = 0;

	// Initial render
	render_map(&game);

	// Set up event hooks
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_hook(game.win, DestroyNotify, 0, handle_close, &game);

	// Start the event loop
	mlx_loop(game.mlx);

	return (0);
}