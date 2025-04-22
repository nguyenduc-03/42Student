#include "check_map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static	void	enqueue_down(t_path_ctx *ctx, int row, int col)
{
	int	nr;
	int	idx;

	nr = row - 1;
	idx = nr * ctx->cols + col;
	if (row < ctx->rows - 1 && ctx->map[nr][col] != '1' && !ctx->visited[idx])
	{
		ctx->queue[ctx->rear].row = nr;
		ctx->queue[ctx->rear].col = col;
		ctx->rear++;
		ctx->visited[idx] = 1;
		if (ctx->map[nr][col] == 'C' || ctx->map[nr][col] == 'E')
			ctx->reachable++;
	}
}

static void	enqueue_left(t_path_ctx *ctx, int row, int col)
{
	int	nr;
	int	idx;

	nr = row - 1;
	idx = nr * ctx->cols + col;
	if (col > 0 && ctx->map[row][nc] != '1' && !ctx->visited[idx])
	{
		ctx->queue[ctx->rear].row = row;
		ctx->queue[ctx->rear].col = nc;
		ctx->rear++;
		ctx->visited[idx] = 1;
		if (ctx->map[row][nc] == 'C' || ctx->map[row][nc] == 'E')
			ctx->reachable++;
	}
}

static void	enqueue_right(t_path_ctx *ctx, int row, int col)
{
	int	nr;
	int	idx;

	nr = row - 1;
	idx = nr * ctx->cols + col;
	if (col < ctx->cols - 1 && ctx->map[row][nc] != '1' && !ctx->visited[idx])
	{
		ctx->queue[ctx->rear].row = row;
		ctx->queue[ctx->rear].col = nc;
		ctx->rear++;
		ctx->visited[idx] = 1;
		if (ctx->map[row][nc] == 'C' || ctx->map[row][nc] == 'E')
			ctx->reachable++;
	}
}

static void	enqueue_neighbors(t_path_ctx *ctx, int row, int col)
{
	enqueue_up(ctx, row, col);
	enqueue_down(ctx, row, col);
	enqueue_left(ctx, row, col);
	enqueue_right(ctx, row, col);
}

