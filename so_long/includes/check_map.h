#ifndef CHECK_MAP_H
# define CHECK_MAP_H
# include<stdio.h>
# include<stdlib.h>
# include <fcntl.h>
# include <unistd.h>


typedef struct  s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		count_c;
	int		count_e;
}			t_map;

typedef struct  s_bfs
{
	int	*visited;
	int	*queue;
	int	head;
	int	tail;
	int	found_c;
	int	exit_reached;
}	t_bfs;


char	**read_map(const char *filename, int *width, int *height);
void	validate_map(char **grid, int width, int height);
int		get_height(const char *path);
int		get_width(const char *path);
void	read_map_file(const char *path, t_map *map);
void	validate_rectangular(t_map *map);
void	validate_borders(t_map *map);
void	validate_chars(t_map *map);
void	validate_paths(t_map *map);
void	free_map(t_map *map);
void	print_error(const char *msg);

#endif
