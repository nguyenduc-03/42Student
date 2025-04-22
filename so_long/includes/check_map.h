#ifndef CHECK_MAP_H
#define CHECK_MAP_H

typedef struct {
	int row;
	int col;
} Position;

// Function to read the map from a file
// Returns a 2D array (null-terminated strings), sets width and height via pointers
char **read_map(const char *filename, int *width, int *height);

// Function to validate the map
// Exits with an error message if invalid, otherwise returns void
void validate_map(char **map, int width, int height);



#endif