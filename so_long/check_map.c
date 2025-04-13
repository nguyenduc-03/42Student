#include "check_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000

// Structure to represent a position in the grid
typedef struct {
    int row;
    int col;
} Position;

// Validates the map's structure
static void validate_structure(char **map, int rows, int cols, int *p_row, int *p_col)
{
    // Check borders
    for (int j = 0; j < cols; j++) {
        if (map[0][j] != '1' || map[rows - 1][j] != '1') {
            write(2, "Error\nMap not surrounded by walls\n", 33);
            exit(1);
        }
    }
    for (int i = 1; i < rows - 1; i++) {
        if (map[i][0] != '1' || map[i][cols - 1] != '1') {
            write(2, "Error\nMap not surrounded by walls\n", 33);
            exit(1);
        }
    }

    // Check characters and count special ones
    int p_count = 0, e_count = 0, c_count = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            char c = map[i][j];
            if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P') {
                write(2, "Error\nInvalid character in map\n", 30);
                exit(1);
            }
            if (c == 'P') {
                p_count++;
                *p_row = i;
                *p_col = j;
            } else if (c == 'E') {
                e_count++;
            } else if (c == 'C') {
                c_count++;
            }
        }
    }

    if (p_count != 1) {
        write(2, "Error\nInvalid number of starting positions\n", 42);
        exit(1);
    }
    if (e_count != 1) {
        write(2, "Error\nInvalid number of exits\n", 30);
        exit(1);
    }
    if (c_count < 1) {
        write(2, "Error\nNo heart in map\n", 23);
        exit(1);
    }
}

// Validates that there is a path from 'P' to all 'C's and 'E'
static void validate_path(char **map, int rows, int cols, int p_row, int p_col)
{
    int *visited = calloc(rows * cols, sizeof(int));
    if (!visited) {
        write(2, "Error\nMemory allocation failed\n", 30);
        exit(1);
    }

    Position *queue = malloc(sizeof(Position) * rows * cols);
    if (!queue) {
        write(2, "Error\nMemory allocation failed\n", 30);
        free(visited);
        exit(1);
    }

    int front = 0, rear = 0;
    queue[rear].row = p_row;
    queue[rear].col = p_col;
    rear++;
    visited[p_row * cols + p_col] = 1;

    while (front < rear) {
        Position current = queue[front];
        front++;
        int row = current.row;
        int col = current.col;

        if (row > 0 && map[row - 1][col] != '1' && !visited[(row - 1) * cols + col]) {
            queue[rear].row = row - 1;
            queue[rear].col = col;
            rear++;
            visited[(row - 1) * cols + col] = 1;
        }
        if (row < rows - 1 && map[row + 1][col] != '1' && !visited[(row + 1) * cols + col]) {
            queue[rear].row = row + 1;
            queue[rear].col = col;
            rear++;
            visited[(row + 1) * cols + col] = 1;
        }
        if (col > 0 && map[row][col - 1] != '1' && !visited[row * cols + col - 1]) {
            queue[rear].row = row;
            queue[rear].col = col - 1;
            rear++;
            visited[row * cols + col - 1] = 1;
        }
        if (col < cols - 1 && map[row][col + 1] != '1' && !visited[row * cols + col + 1]) {
            queue[rear].row = row;
            queue[rear].col = col + 1;
            rear++;
            visited[row * cols + col + 1] = 1;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ((map[i][j] == 'C' || map[i][j] == 'E') && !visited[i * cols + j]) {
                write(2, "Error\nNo valid path to all heart and exit\n", 43);
                free(visited);
                free(queue);
                exit(1);
            }
        }
    }

    free(visited);
    free(queue);
}

char **read_map(const char *filename, int *width, int *height)
{
    FILE *file = fopen(filename, "r");
    if (!file) {
        write(2, "Error\nFile not found\n", 21);
        exit(1);
    }

    char *map[MAX_ROWS];
    int rows = 0;
    char buffer[1024];
    int cols;

    while (fgets(buffer, sizeof(buffer), file) != NULL && rows < MAX_ROWS) {
        size_t len = strlen(buffer);
        while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
            buffer[len - 1] = '\0';
            len--;
        }
        if (rows == 0) {
            cols = len;
        } else if (len != (size_t)cols) {
            write(2, "Error\nMap is not rectangular\n", 28);
            fclose(file);
            exit(1);
        }

        map[rows] = malloc(len + 1);
        if (!map[rows]) {
            write(2, "Error\nMemory allocation failed\n", 30);
            fclose(file);
            exit(1);
        }
        strcpy(map[rows], buffer);
        rows++;
    }
    fclose(file);

    if (rows == 0) {
        write(2, "Error\nEmpty map\n", 16);
        exit(1);
    }

    char **result = malloc(sizeof(char *) * (rows + 1));
    if (!result) {
        write(2, "Error\nMemory allocation failed\n", 30);
        exit(1);
    }
    for (int i = 0; i < rows; i++)
        result[i] = map[i];
    result[rows] = NULL;

    *width = cols;
    *height = rows;
    return result;
}

void validate_map(char **map, int width, int height)
{
    if (!map || height == 0) {
        write(2, "Error\nEmpty map\n", 16);
        exit(1);
    }

    int p_row, p_col;
    validate_structure(map, height, width, &p_row, &p_col);
    validate_path(map, height, width, p_row, p_col);
}