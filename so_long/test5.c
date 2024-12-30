#include <mlx.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define TILE_SIZE 64

// Game state structure
typedef struct s_game {
    void    *mlx;
    void    *win;
    char    **map;
    int     rows;
    int     cols;
    int     player_x;
    int     player_y;
    int     moves;
    void    *wall_img;
    void    *player_img;
    void    *collectible_img;
    void    *exit_img;
    void    *enemy_img;
    int     collectibles;
    bool    game_over;
} t_game;

// Error handling
void error_exit(const char *message) {
    write(2, "Error\n", 6);
    write(2, message, strlen(message));
    exit(1);
}

// Count rows and columns in the map
void count_map_size(const char *file, t_game *game) {
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file\n");
    
    char buf;
    int cols = 0, rows = 0;
    bool new_row = true;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            rows++;
            new_row = true;
        } else {
            if (new_row) {
                game->cols = cols;
                cols = 0;
                new_row = false;
            }
            cols++;
        }
    }
    close(fd);
    game->rows = rows;
}

// Read the map from the file
void read_map(const char *file, t_game *game) {
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file\n");
    
    game->map = malloc(sizeof(char *) * game->rows);
    if (!game->map)
        error_exit("Memory allocation failed\n");

    for (int i = 0; i < game->rows; i++) {
        game->map[i] = malloc(sizeof(char) * (game->cols + 1));
        if (!game->map[i])
            error_exit("Memory allocation failed\n");
        read(fd, game->map[i], game->cols + 1);
        game->map[i][game->cols] = '\0';
    }
    close(fd);
}

// Validate the map
void validate_map(t_game *game) {
    int player_count = 0, exit_count = 0, collectible_count = 0;

    for (int y = 0; y < game->rows; y++) {
        for (int x = 0; x < game->cols; x++) {
            char tile = game->map[y][x];

            if (tile == 'P') {
                player_count++;
                game->player_x = x;
                game->player_y = y;
            } else if (tile == 'E') {
                exit_count++;
            } else if (tile == 'C') {
                collectible_count++;
            } else if (tile != '0' && tile != '1') {
                error_exit("Invalid character in map\n");
            }
        }
    }
    if (player_count != 1 || exit_count != 1 || collectible_count < 1)
        error_exit("Map must contain exactly 1 player, 1 exit, and at least 1 collectible\n");

    game->collectibles = collectible_count;
}

// Draw the map
void draw_map(t_game *game) {
    for (int y = 0; y < game->rows; y++) {
        for (int x = 0; x < game->cols; x++) {
            void *img = NULL;
            if (game->map[y][x] == '1')
                img = game->wall_img;
            else if (game->map[y][x] == 'P')
                img = game->player_img;
            else if (game->map[y][x] == 'C')
                img = game->collectible_img;
            else if (game->map[y][x] == 'E')
                img = game->exit_img;
            if (img)
                mlx_put_image_to_window(game->mlx, game->win, img, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}

// Handle key press
int handle_keypress(int key, t_game *game) {
    if (key == 65307) // Escape key
        exit(0);

    // Movement logic
    return (0);
}

// Main function
int main(int argc, char **argv) {
    if (argc != 2)
        error_exit("Usage: ./game map.ber\n");

    t_game game;
    count_map_size(argv[1], &game);
    read_map(argv[1], &game);
    validate_map(&game);

    // Initialize game window and resources
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, game.cols * TILE_SIZE, game.rows * TILE_SIZE, "So Long");

    // Load images
    game.wall_img = mlx_xpm_file_to_image(game.mlx, "wall.xpm", &TILE_SIZE, &TILE_SIZE);
    game.player_img = mlx_xpm_file_to_image(game.mlx, "character.xpm", &TILE_SIZE, &TILE_SIZE);
    game.collectible_img = mlx_xpm_file_to_image(game.mlx, "heart.xpm", &TILE_SIZE, &TILE_SIZE);
    game.exit_img = mlx_xpm_file_to_image(game.mlx, "portal.xpm", &TILE_SIZE, &TILE_SIZE);

    draw_map(&game);
    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);

    return 0;
}
