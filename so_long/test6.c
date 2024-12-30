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
    int     collectibles;
    bool    game_over;
} t_game;

// Utility for error handling
void error_exit(const char *message) {
    write(2, "Error\n", 6);
    write(2, message, strlen(message));
    exit(1);
}

// Function to count rows and columns of the map
// Adjust size calculation logic to demand uniformity.
void count_map_size(const char *file, t_game *game) {
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file\n");

    char buf;
    int cols = 0, rows = 0, max_cols = 0;
    bool new_line_started = true;
    
    while (read(fd, &buf, 1) > 0) {
        // Since each line should be consistently sized maximize the largest:
        if (buf == '\n') {
            if (cols > 0 || new_line_started) {
                rows++;
            }
            max_cols = (cols > max_cols) ? cols : max_cols;
            cols = 0;
            new_line_started = true;
        } else {
            cols++;
            new_line_started = false;
        }
    }

    // Account for the last row if it doesn't end with '\n'
    if (cols > 0) {
        rows++;
        max_cols = (cols > max_cols) ? cols : max_cols;
    }

    close(fd);
    game->rows = rows;
    game->cols = max_cols;  // Use maximum column in struct

    printf("Map size: %d rows, %d columns\n", game->rows, game->cols);
}

// Function to read the map file
void read_map(const char *file, t_game *game) {
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        error_exit("Failed to open map file\n");

    game->map = malloc(sizeof(char *) * game->rows);
    if (!game->map)
        error_exit("Memory allocation failed\n");

    char buffer[game->cols + 1]; // Buffer accommodating longest line
    
    for (int i = 0; i < game->rows; i++) {
        ssize_t bytes_read;
        char c;
        int col = 0;
        while ((bytes_read = read(fd, &c, 1)) > 0 && c != '\n' && col < game->cols) {
            buffer[col++] = c;
        }
        buffer[col] = '\0';
        
        if (bytes_read < 0 || (c != '\n' && c != '\0' && col != game->cols)) {
            error_exit("Map dimensions inconsistent\n");
        }

        game->map[i] = malloc(sizeof(char) * (game->cols + 1));
        if (!game->map[i])
            error_exit("Memory allocation failed\n");
        strcpy(game->map[i], buffer);
    }
    close(fd);
}

#define MAX_QUEUE_SIZE 10000

typedef struct {
    int x, y;
} Point;

bool is_valid_move(t_game *game, bool **visited, int x, int y) {
    return (x >= 0 && x < game->cols && y >= 0 && y < game->rows &&
            !visited[y][x] && (game->map[y][x] == '0' || 
            game->map[y][x] == 'C' || game->map[y][x] == 'E'));
}

bool path_exists(t_game *game) {
    bool **visited = malloc(sizeof(bool *) * game->rows);
    for (int i = 0; i < game->rows; i++) {
        visited[i] = malloc(sizeof(bool) * game->cols);
        memset(visited[i], false, sizeof(bool) * game->cols);
    }

    Point queue[MAX_QUEUE_SIZE];
    int front = 0, rear = 0;

    queue[rear++] = (Point){game->player_x, game->player_y};
    visited[game->player_y][game->player_x] = true;

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int found_collectibles = 0;
    bool exit_found = false;

    while (front < rear) {
        Point current = queue[front++];

        for (int i = 0; i < 4; i++) {
            int nx = current.x + directions[i][0];
            int ny = current.y + directions[i][1];

            if (is_valid_move(game, visited, nx, ny)) {
                if (game->map[ny][nx] == 'C') {
                    found_collectibles++;
                }
                if (game->map[ny][nx] == 'E') {
                    exit_found = true;
                }
                visited[ny][nx] = true;
                queue[rear++] = (Point){nx, ny};
            }
        }
    }

    for (int i = 0; i < game->rows; i++) {
        free(visited[i]);
    }
    free(visited);

    return (found_collectibles == game->collectibles && exit_found);
}

// Validate the map
void validate_map(t_game *game) {
    int player_count = 0, exit_count = 0, collectible_count = 0;

    // Validate the borders and components of the map
    for (int y = 0; y < game->rows; y++) {
        for (int x = 0; x < game->cols; x++) {
            char tile = game->map[y][x];

            if ((y == 0 || y == game->rows - 1) && tile != '1') {
                printf("Error: Map must be surrounded by walls at position (%d, %d)\n", x, y);
                error_exit("Map must be surrounded by walls\n");
            }
            if ((x == 0 || x == game->cols - 1) && tile != '1' && y != 0 && y != game->rows - 1) {
                printf("Error: Map must be surrounded by walls at position (%d, %d)\n", x, y);
                error_exit("Map must be surrounded by walls\n");
            }

            if (tile == 'P') {
                player_count++;
                game->player_x = x;
                game->player_y = y;
            } else if (tile == 'E') {
                exit_count++;
            } else if (tile == 'C') {
                collectible_count++;
            } else if (tile != '0' && tile != '1') {
                printf("Error: Invalid character in map at position (%d, %d)\n", x, y);
                error_exit("Invalid character in map\n");
            }
        }
    }

    if (player_count != 1 || exit_count != 1 || collectible_count < 1) {
        error_exit("Map must contain exactly 1 player, 1 exit, and at least 1 collectible\n");
    }

    game->collectibles = collectible_count;

    // Validate that a path exists from the player to exit via all collectibles
    if (!path_exists(game)) {
        error_exit("There is no valid path to collect all collectibles and reach the exit\n");
    }
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

int handle_keypress(int keycode, t_game *game) {
    if (keycode == 65307) { // ESC key
        mlx_destroy_window(game->mlx, game->win);
        exit(0);
    }

    int new_x = game->player_x;
    int new_y = game->player_y;

    // Update coordinates based on key press
    if (keycode == 97 && game->map[new_y][new_x - 1] != '1') { // 'A' key (left)
        new_x--;
    } else if (keycode == 115 && game->map[new_y + 1][new_x] != '1') { // 'S' key (down)
        new_y++;
    } else if (keycode == 100 && game->map[new_y][new_x + 1] != '1') { // 'D' key (right)
        new_x++;
    } else if (keycode == 119 && game->map[new_y - 1][new_x] != '1') { // 'W' key (up)
        new_y--;
    }

    // Update player position if movement is valid
    if ((new_x != game->player_x) || (new_y != game->player_y)) {
        game->player_x = new_x;
        game->player_y = new_y;
        game->moves++;

        // Handle collecting items
        if (game->map[new_y][new_x] == 'C') {
            game->map[new_y][new_x] = '0';
            game->collectibles--;
        }

        // Check if reached exit
        if (game->map[new_y][new_x] == 'E' && game->collectibles == 0) {
            printf("Congratulations! You've completed the game in %d moves.\n", game->moves);
            game->game_over = true;
            mlx_destroy_window(game->mlx, game->win);
            exit(0);
        }

        // Redraw the map
        mlx_clear_window(game->mlx, game->win);
        draw_map(game);
    }

    return (0);
}

// Function to handle window close with "X" button
int handle_close(t_game *game) {
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
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
    
    // Load images with error checking
    int width = TILE_SIZE;
    int height = TILE_SIZE;

    game.wall_img = mlx_xpm_file_to_image(game.mlx, "wall.xpm", &width, &height);
    if (!game.wall_img) 
        error_exit("Failed to load wall image\n");

    game.player_img = mlx_xpm_file_to_image(game.mlx, "character.xpm", &width, &height);
    if (!game.player_img) 
        error_exit("Failed to load player image\n");

    game.collectible_img = mlx_xpm_file_to_image(game.mlx, "heart.xpm", &width, &height);
    if (!game.collectible_img) 
        error_exit("Failed to load collectible image\n");

    game.exit_img = mlx_xpm_file_to_image(game.mlx, "portal.xpm", &width, &height);
    if (!game.exit_img) 
        error_exit("Failed to load exit image\n");

    draw_map(&game);
    mlx_key_hook(game.win, handle_keypress, &game);
    mlx_loop(game.mlx);

    return 0;
}