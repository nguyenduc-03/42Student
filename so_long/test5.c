#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>    // For printf
#include <X11/X.h>    // For KeyPress, KeyPressMask, DestroyNotify
#include "check_map.h"

// Assuming check_map.h provides these functions
char **read_map(const char *filename, int *width, int *height);
void validate_map(char **map, int width, int height);

typedef struct s_game {
    void    *mlx;
    void    *win;
    char    **map;
    int     map_width;
    int     map_height;
    void    *wall_img;
    void    *background_img;
    void    *heart_img;
    void    *exit_img;
    void    *player_img;
    int     img_width;
    int     img_height;
    int     player_x;
    int     player_y;
    int     heart;
    int     moves;
} t_game;

// Function to render the map and player
void render_map(t_game *game)
{
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
    mlx_destroy_window(game->mlx, game->win);
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
    game.win = mlx_new_window(game.mlx, width * tile_size, height * tile_size, "so_long");
    if (!game.win)
    {
        write(2, "Error: Failed to create window\n", 31);
        exit(1);
    }

    // Load images (adjust paths based on your xpm/ directory)
    game.wall_img = mlx_xpm_file_to_image(game.mlx, "./xpm/wall.xpm", &game.img_width, &game.img_height);
    if (!game.wall_img)
    {
        write(2, "Error: Failed to load wall.xpm\n", 31);
        exit(1);
    }
    game.background_img = mlx_xpm_file_to_image(game.mlx, "./xpm/background.xpm", &game.img_width, &game.img_height);
    if (!game.background_img)
    {
        write(2, "Error: Failed to load background.xpm\n", 32);
        exit(1);
    }
    game.heart_img = mlx_xpm_file_to_image(game.mlx, "./xpm/heart.xpm", &game.img_width, &game.img_height);
    if (!game.heart_img)
    {
        write(2, "Error: Failed to load heart.xpm\n", 33);
        exit(1);
    }
    game.exit_img = mlx_xpm_file_to_image(game.mlx, "./xpm/exit.xpm", &game.img_width, &game.img_height);
    if (!game.exit_img)
    {
        write(2, "Error: Failed to load exit.xpm\n", 31);
        exit(1);
    }
    game.player_img = mlx_xpm_file_to_image(game.mlx, "./xpm/player.xpm", &game.img_width, &game.img_height);
    if (!game.player_img)
    {
        write(2, "Error: Failed to load player.xpm\n", 33);
        exit(1);
    }

    // Set game state
    game.map = map;
    game.map_width = width;
    game.map_height = height;
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