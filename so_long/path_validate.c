#include "check_map.h"

static void	visit_horiz(t_map *map, t_bfs *bfs, int cx, int cy)
{
	if (cx - 1 >= 0 && !bfs->visited[cy * map->width + (cx - 1)]
		&& map->grid[cy][cx - 1] != '1')
	{
		bfs->visited[cy * map->width + (cx - 1)] = 1;
		if (map->grid[cy][cx - 1] == 'C')
			bfs->found_c++;
		if (map->grid[cy][cx - 1] == 'E')
			bfs->exit_reached = 1;
		bfs->queue[bfs->tail * 2] = cx - 1;
		bfs->queue[bfs->tail * 2 + 1] = cy;
		bfs->tail++;
	}
	if (cx + 1 < map->width && !bfs->visited[cy * map->width + (cx + 1)]
		&& map->grid[cy][cx + 1] != '1')
	{
		bfs->visited[cy * map->width + (cx + 1)] = 1;
		if (map->grid[cy][cx + 1] == 'C')
			bfs->found_c++;
		if (map->grid[cy][cx + 1] == 'E')
			bfs->exit_reached = 1;
		bfs->queue[bfs->tail * 2] = cx + 1;
		bfs->queue[bfs->tail * 2 + 1] = cy;
		bfs->tail++;
	}
}

static void	visit_vert(t_map *map, t_bfs *bfs, int cx, int cy)
{
	if (cy - 1 >= 0 && !bfs->visited[(cy - 1) * map->width + cx]
		&& map->grid[cy - 1][cx] != '1')
	{
		bfs->visited[(cy - 1) * map->width + cx] = 1;
		if (map->grid[cy - 1][cx] == 'C')
			bfs->found_c++;
		if (map->grid[cy - 1][cx] == 'E')
			bfs->exit_reached = 1;
		bfs->queue[bfs->tail * 2] = cx;
		bfs->queue[bfs->tail * 2 + 1] = cy - 1;
		bfs->tail++;
	}
	if (cy + 1 < map->height && !bfs->visited[(cy + 1) * map->width + cx]
		&& map->grid[cy + 1][cx] != '1')
	{
		bfs->visited[(cy + 1) * map->width + cx] = 1;
		if (map->grid[cy + 1][cx] == 'C')
			bfs->found_c++;
		if (map->grid[cy + 1][cx] == 'E')
			bfs->exit_reached = 1;
		bfs->queue[bfs->tail * 2] = cx;
		bfs->queue[bfs->tail * 2 + 1] = cy + 1;
		bfs->tail++;
	}
}

static void	explore(t_map *map, t_bfs *bfs, int cx, int cy)
{
	visit_horiz(map, bfs, cx, cy);
	visit_vert(map, bfs, cx, cy);
}

void	validate_paths(t_map *map)
{
	t_bfs	bfs;
	int		i[2];

	bfs.visited = malloc(sizeof(int) * map->height * map->width);
	bfs.queue = malloc(sizeof(int) * map->height * map->width * 2);
	if (!bfs.visited || !bfs.queue)
		print_error("Malloc error from bfd_visite");
	bfs.head = 0;
	bfs.tail = 1;
	bfs.found_c = 0;
	bfs.exit_reached = 0;
	bfs.visited[map->player_y * map->width + map->player_x] = 1;
	bfs.queue[0] = map->player_x;
	bfs.queue[1] = map->player_y;
	while (bfs.head < bfs.tail)
	{
		i[0] = bfs.queue[bfs.head * 2];
		i[1] = bfs.queue[bfs.head * 2 + 1];
		bfs.head++;
		explore(map, &bfs, i[0], i[1]);
	}
	free(bfs.visited);
	free(bfs.queue);
	if (bfs.found_c != map->count_c || !bfs.exit_reached)
		{
			print_error("pathvalidate");
			exit(EXIT_FAILURE);}
}
