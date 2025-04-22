#include "check_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void init_path_ctx(t_path_ctx *ctx, t_map_params *params);
static void enqueue_neighbors(t_path_ctx *ctx, int row, int col);

static void	bfs_traverse(t_path_ctx *ctx)
{
	Position	cur;

	while (ctx->front < ctx->rear)
	{
		cur = ctx->queue[ctx->front++];
		enqueue_neighbors(ctx, cur.row, cur.col);
	}
}

static void	validate_path(char **map, int *rows, int *cols, t_map_meta *meta)
{
	t_path_ctx	ctx;

	t_map_params	params;

params.map = map;
params.rows = *rows;
params.cols = *cols;
params.start_row = meta->p_row;
params.start_col = meta->p_col;

init_path_ctx(&ctx, &params);

	bfs_traverse(&ctx);
	if (ctx.reachable < meta->c_count + meta->e_count)
	{
		write(2, "Error\nNo valid path to all heart and exit\n", 43);
		free(ctx.visited);
		free(ctx.queue);
		exit(1);
	}
	free(ctx.visited);
	free(ctx.queue);
}

static void	enqueue_up(t_path_ctx *ctx, int row, int col)
{
	int	nr;
	int	idx;

	nr = row - 1;
	idx = nr * ctx->cols + col;
	if (row > 0 && ctx->map[nr][col] != '1' && !ctx->visited[idx])
	{
		ctx->queue[ctx->rear].row = nr;
		ctx->queue[ctx->rear].col = col;
		ctx->rear++;
		ctx->visited[idx] = 1;
		if (ctx->map[nr][col] == 'C' || ctx->map[nr][col] == 'E')
			ctx->reachable++;
	}
}

static	void	init_path_ctx(t_path_ctx *ctx, t_map_params *params)
{
	int	k;

	k = 0;
	ctx->map = params->map;
	ctx->rows = params->rows;
	ctx->cols = params->cols;
	ctx->visited = malloc(ctx->rows * ctx->cols * sizeof(int));
	if (!ctx->visited)
		write(1, "Error\nMemory allocation failed\n", 30);
	while (k < ctx->rows * ctx->cols)
		ctx->visited[k++] = 0;
	ctx->queue = malloc(sizeof(Position) * ctx->rows * ctx->cols);
	if (!ctx->queue)
	{
		free(ctx->visited);
		write(1, "Error\nMemory allocation failed\n", 30);
	}
	ctx->front = 0;
	ctx->rear = 0;
	ctx->reachable = 0;
	ctx->queue[ctx->rear].row = params->start_row;
	ctx->queue[ctx->rear].col = params->start_col;
	ctx->rear++;
	ctx->visited[params->start_row * ctx->cols + params->start_col] = 1;
}
