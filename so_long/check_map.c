#include "check_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000
#define BUF_SIZE 4096
	
// Structure to represent a position in the grid

// Validates the map's structure
// Helper: ensure map borders are walls without loops (<=25 lines, while loops)
static void check_borders(char **map, int rows, int cols)
{
    int j = 0;
    while (j < cols) {
        if (map[0][j] != '1' || map[rows - 1][j] != '1') {
            write(2, "Error\nMap not surrounded by walls\n", 33);
            exit(1);
        }
        j++;
    }
    int i = 1;
    while (i < rows - 1) {
        if (map[i][0] != '1' || map[i][cols - 1] != '1') {
            write(2, "Error\nMap not surrounded by walls\n", 33);
            exit(1);
        }
        i++;
    }
}

// Helper: validate characters and count specials without nested loops (<=25 lines)
static void count_and_validate_chars( char **map, int rows, int cols, int *p_row, int *p_col ) {
    int p_count = 0;
    int e_count = 0;
    int c_count = 0;
    int idx = 0;
    int total = rows * cols;
    while (idx < total) {
        char c = map[idx / cols][idx % cols];
        if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P') {
            write(2, "Error\nInvalid character in map\n", 30);
            exit(1);
        }
        if (c == 'P') { p_count++; *p_row = idx / cols; *p_col = idx % cols; }
        if (c == 'E') e_count++;
        if (c == 'C') c_count++;
        idx++;
    }
    if (p_count != 1) { write(2, "Error\nInvalid number of starting positions\n", 42); exit(1); }
    if (e_count != 1) { write(2, "Error\nInvalid number of exits\n", 30); exit(1); }
    if (c_count < 1)  { write(2, "Error\nNo heart in map\n", 23); exit(1); }
}

// Reconstructed validate_structure using the two helpers
static void validate_structure(char **map, int rows, int cols, int *p_row, int *p_col)
{
    check_borders(map, rows, cols);
    count_and_validate_chars(map, rows, cols, p_row, p_col);
}


// Helper: initialize BFS queue (<=25 lines)
static Position *init_queue(int rows, int cols,
    int *front, int *rear,
    int start_row, int start_col,
    int *visited)
{
    Position *queue = malloc(sizeof(Position) * rows * cols);
    if (!queue) {
        write(2, "Error\nMemory allocation failed\n", 30);
        free(visited);
        exit(1);
    }
    *front = 0;
    *rear = 0;
    queue[*rear].row = start_row;
    queue[*rear].col = start_col;
    (*rear)++;
    visited[start_row * cols + start_col] = 1;
    return queue;
}

// Helper: enqueue a valid neighbor (<=25 lines)
static void enqueue_neighbor(
    char **map, int rows, int cols,
    Position *queue, int *rear,
    int nr, int nc,
    int *visited
) {
    int idx = nr * cols + nc;
    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
        map[nr][nc] != '1' && !visited[idx]) {
        queue[*rear].row = nr;
        queue[*rear].col = nc;
        (*rear)++;
        visited[idx] = 1;
    }
}

// Helper: perform BFS traversal (<=25 lines)
static void bfs_traverse(
    char **map, int rows, int cols,
    int start_row, int start_col,
    int *visited
) {
    int front;
    int rear;
    Position *queue = init_queue(
        rows, cols, &front, &rear,
        start_row, start_col,
        visited
    );
    while (front < rear) {
        Position cur = queue[front++];
        int r = cur.row;
        int c = cur.col;
        enqueue_neighbor(map, rows, cols, queue, &rear, r - 1, c, visited);
        enqueue_neighbor(map, rows, cols, queue, &rear, r + 1, c, visited);
        enqueue_neighbor(map, rows, cols, queue, &rear, r, c - 1, visited);
        enqueue_neighbor(map, rows, cols, queue, &rear, r, c + 1, visited);
    }
    free(queue);
}

// Reconstructed validate_path using helpers
static void validate_path(
    char **map, int rows, int cols,
    int p_row, int p_col
) {
    int total = rows * cols;
    int *visited = calloc(total, sizeof(int));
    if (!visited) {
        write(2, "Error\nMemory allocation failed\n", 30);
        exit(1);
    }
    bfs_traverse(map, rows, cols, p_row, p_col, visited);
    int idx = 0;
    while (idx < total) {
        char ch = map[idx / cols][idx % cols];
        if ((ch == 'C' || ch == 'E') && !visited[idx]) {
            write(2, "Error\nNo valid path to all heart and exit\n", 43);
            free(visited);
            exit(1);
        }
        idx++;
    }
    free(visited);
}


static char *read_file(int fd, int *out_size);
static void split_lines(char *data, int size, char **rows_data, int *rows, int *cols);
static char **build_map(char **rows_data, int rows);
static void fail_empty_map(void);

char **read_map(const char *filename, int *width, int *height)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0) { perror("open"); exit(1); }

    int size;
    char *data = read_file(fd, &size);
    close(fd);

    char *rows_data[MAX_ROWS];
    int rows = 0, cols = 0;
    split_lines(data, size, rows_data, &rows, &cols);

    if (rows == 0) fail_empty_map();

    char **map = build_map(rows_data, rows);
    *width = cols;
    *height = rows;
    return map;
}

// Helper: read entire file into buffer
static char *read_file(int fd, int *out_size)
{
    char *data = malloc(BUF_SIZE);
    if (!data) { write(2, "Error\nMemory allocation failed\n", 30); exit(1); }
    int cap = BUF_SIZE, total = 0;
    while (1) {
        int n = read(fd, data + total, cap - total);
        if (n < 0) { perror("read"); exit(1); }
        if (n == 0) break;
        total += n;
        if (total == cap) {
            cap *= 2;
            char *tmp = realloc(data, cap);
            if (!tmp) { write(2, "Error\nMemory allocation failed\n", 30); exit(1); }
            data = tmp;
        }
    }
    *out_size = total;
    return data;
}

// Helper: trim newline/carriage and split into lines
static void split_lines(char *data, int size, char **rows_data, int *rows, int *cols)
{
    int r = 0;
    char *line = data;
    for (int i = 0; i <= size; i++) {
        if (i == size || data[i] == '\n' || data[i] == '\r') {
            int len = &data[i] - line;
            // remove trailing CR/LF
            while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) len--;
            if (r == 0) *cols = len;
            else if (len != *cols) { write(2, "Error\nMap is not rectangular\n", 28); exit(1); }
            line[len] = '\0';
            rows_data[r++] = line;
            line = &data[i+1];
            if (r >= MAX_ROWS) break;
        }
    }
    *rows = r;
}

// Helper: allocate and populate map array
static char **build_map(char **rows_data, int rows)
{
    char **map = malloc((rows+1) * sizeof(char *));
    if (!map) { write(2, "Error\nMemory allocation failed\n", 30); exit(1); }
    for (int i = 0; i < rows; i++) map[i] = rows_data[i];
    map[rows] = NULL;
    return map;
}

// Helper: handle empty map error
static void fail_empty_map(void)
{
    write(2, "Error\nEmpty map\n", 16);
    exit(1);
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
