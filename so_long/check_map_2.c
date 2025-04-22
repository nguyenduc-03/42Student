#include "check_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
