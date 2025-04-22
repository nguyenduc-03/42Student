#include "game.h"
#include <unistd.h>
#include <stdlib.h>
#include <X11/keysym.h>

#define KEY_ESC XK_Escape
#define KEY_W XK_w
#define KEY_S XK_s
#define KEY_A XK_a
#define KEY_D XK_d

static void	print_msg(const char *p, int m, int e)
{
	char	b[12];
	char	msg[40];
	char	c;
	int		i;
	int		j;
	int		t;
	int		lp;

	i = 0;
	t = m;
	if (t == 0)
		b[i++] = '0';
	while (t /= 10)
		b[i++] = '0' + (t % 10);
	j = 0;
	while (j++ < i / 2)
	{
		c = b[j];
		b[j] = b[i - 1 - j];
		b[i - 1 - j] = c;
	}
	lp = 0;
	while (p[lp++]) 
		msg[lp] = p[lp];
	t = 0;
	while (t++ < i) 
		msg[lp + t] = b[t];
	msg[lp + t] = '\n';
	write(1, msg, lp + t + 1);
	if (e)
		exit(0);
}

static	void	move_player(t_game *g, int nx, int ny)
{
	char n;
	if (nx < 0 || nx >= g->map_width || ny < 0 || ny >= g->map_height)
		return ;
	n = g->map[ny][nx];
	if (n == '1')
		return ;
	if (n == '0' || n == 'C')
	{
		if (n == 'C') g->heart--;
		g->map[ny][nx] = '0';
		g->player_x = nx; g->player_y = ny; g->moves++;
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
		exit(0);
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

void	start_game(char **m, int w, int h, int px, int py, int hearts)
{
	t_game	g;

	g.mlx = mlx_init();
	if (!g.mlx)
		write(2, "Error: MLX init failed\n", 24);
	g.map = m;
	g.map_width = w;
	g.map_height = h;
	g.img_width = 32;
	g.img_height = 32;
	g.win = mlx_new_window(g.mlx, w * 32, h * 32, "so_long");
	if (!g.win)
		write(2, "Error: Window creation failed\n", 30);
	g.player_x = px;
	g.player_y = py;
	g.heart	= hearts;
	g.moves	= 0;
	load_images(&g);
	render_map(&g);
	mlx_hook(g.win, 2, 1L << 0, handle_keypress, &g);
	mlx_hook(g.win, 17, 0, handle_close, &g);
	mlx_loop(g.mlx);
}
