#include "game.h"
#include "check_map.h"
#include <unistd.h>
#include <stdlib.h>
#include <X11/keysym.h>

#define KEY_ESC XK_Escape
#define KEY_W XK_w
#define KEY_S XK_s
#define KEY_A XK_a
#define KEY_D XK_d

static	int	fmt_num(char *buf, int n)
{
	int		vars[3];
	char	c;

	vars[0] = 0;
	vars[1] = n;
	if (!vars[1])
		buf[vars[0]++] = '0';
	while (vars[1])
	{
		buf[vars[0]++] = '0' + (vars[1] % 10);
		vars[1] /= 10;
	}
	vars[2] = 0;
	while (vars[2] < vars[0] / 2)
	{
		c = buf[vars[2]];
		buf[vars[2]] = buf[vars[0] - 1 - vars[2]];
		buf[vars[0] - 1 - vars[2]] = c;
		vars[2]++;
	}
	return (vars[0]);
}

static void	print_msg(const char *p, int m, int e)
{
	char	num[12];
	char	msg[40];
	int		vars[4];

	vars[0] = 0;
	while (p[vars[0]])
	{
		msg[vars[0]] = p[vars[0]];
		vars[0]++;
	}
	vars[1] = fmt_num(num, m);
	vars[2] = 0;
	while (vars[2] < vars[1])
	{
		msg[vars[0] + vars[2]] = num[vars[2]];
		vars[2]++;
	}
	vars[3] = vars[0] + vars[1];
	msg[vars[3]] = '\n';
	vars[3]++;
	write(1, msg, vars[3]);
	if (e)
		exit(0);
}

static	void	move_player(t_game *g, int nx, int ny)
{
	char	n;

	if (nx < 0 || nx >= g->map_width || ny < 0 || ny >= g->map_height)
		return ;
	n = g->map[ny][nx];
	if (n == '1')
		return ;
	if (n == '0' || n == 'C')
	{
		if (n == 'C')
			g->heart--;
		g->map[ny][nx] = '0';
		g->player_x = nx;
		g->player_y = ny;
		g->moves++;
		print_msg("Moves: ", g->moves, 0);
		render_map(g);
	}
	else if (n == 'E' && g->heart == 0)
		print_msg("You win! Moves: ", g->moves, 1);
}

int	handle_keypress(int keycode, t_game *g)
{
	int	x;
	int	y;

	x = g->player_x;
	y = g->player_y;
	if (keycode == KEY_ESC)
		{print_error("handle_keypress");
			exit(0);}
	else if (keycode == KEY_W)
		move_player(g, x, y - 1);
	else if (keycode == KEY_S)
		move_player(g, x, y + 1);
	else if (keycode == KEY_A)
		move_player(g, x - 1, y);
	else if (keycode == KEY_D)
		move_player(g, x + 1, y);
	return (0);
}

void	start_game(char **m, int i[5])
{
	t_game	g;

	g.mlx = mlx_init();
	if (!g.mlx)
		write(2, "Error: MLX init failed\n", 24);
	g.map = m;
	g.map_width = i[0];
	g.map_height = i[1];
	g.img_width = 32;
	g.img_height = 32;
	g.win = mlx_new_window(g.mlx, i[0] * 32, i[1] * 32, "so_long");
	if (!g.win)
		write(2, "Error: Window creation failed\n", 30);
	g.player_x = i[2];
	g.player_y = i[3];
	g.heart = i[4];
	g.moves = 0;
	load_images(&g);
	render_map(&g);
	mlx_hook(g.win, 2, 1L << 0, handle_keypress, &g);
	mlx_hook(g.win, 17, 0, handle_close, &g);
	mlx_loop(g.mlx);
}

/*Original Variable | New Notation (i[index]) | Description
i | i[0] | Used for index while building number string
j | i[1] | Used in swapping
t | i[2] | Temp for number, loop, etc.
lp | i[3] | Length pointer for message prefix */