#include "mlx.h"
#include "qwerty.h"
#include <stdio.h>
#include <stdlib.h>  
#include <math.h>
#include <stdbool.h>
#include <time.h>

#ifdef DEBUG
#include "_debug.h"
#endif

int Worldmap[16][16] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vector;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

t_vector	deltadist(t_vector ray)
{
	t_vector	delta;
	
	if (ray.y == 0)
		delta.x = 0;
	else if (ray.x == 0)
		delta.x = 1;
	else
		delta.x = abs(1 / ray.x);
	if (ray.x == 0)
		delta.y = 0;
	else if (ray.y == 0)
		delta.y = 1;
	else
		delta.y = abs(1 / ray.y);
	return (delta);
}

void	img_pixel_put(t_img *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	put_row(t_img *img, int x, int top_y, int bot_y, int color)
{
	while (top_y <= bot_y)
	{
		img_pixel_put(img, x, top_y, color);
		top_y++;
	}
}

typedef struct	s_player
{
	t_vector	coord;
	t_vector	dir;
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	char		*title;
	t_img		*img;
	t_player	player;
}			t_window;

int	render_engine(t_window *win)
{
	t_vector	camera = {0, 0.66};
	t_player	*player = &win->player;
	time_t	ms_frame = 0;
	time_t	ms_lastframe = 0;

	for (int x = 0; x < win->width; x++)
	{
		double		camx = 2 * x / (double)win->width - 1;
		t_vector	ray = {player->dir.x + camera.y * camx, player->dir.y + camera.y * camx};
		t_vector	delta = deltadist(ray);
		t_vector	map = {player->coord.x * 1.0, player->coord.y * 1.0};
		t_vector	distside;
		double		distwall_orth;
		t_vector	step;
		bool 		hit = false;
		int			hit_side;

		if (ray.x < 0)
		{
			step.x = -1;
			distside.x = (player->coord.x - map.x) * delta.x;
		}
		else
		{
			step.x = 1;
			distside.x = (map.x + 1.0 - player->coord.x) * delta.x;
		}
		if (ray.y < 0)
		{
			step.y = -1;
			distside.y = (player->coord.y - map.y) * delta.y;
		}
		else
		{
			step.y = 1;
			distside.y = (map.y + 1.0 - player->coord.y) * delta.y;
		}
		while (hit == false)
		{
			if (distside.x < distside.y)
			{
				distside.x += delta.x;
				map.x += step.x;
				hit_side = 0;
			}
			else
			{
				distside.y += delta.y;
				map.y += step.y;
				hit_side = 1;
			}
			if (Worldmap[(int)map.x][(int)map.y] > 0)
				hit = true;
		}
		if (hit_side == 0)
			distwall_orth = (map.x - player->coord.x + (2 - step.x) / 2 ) / ray.x;
		else
			distwall_orth = (map.y - player->coord.y + (2 - step.y) / 2 ) / ray.y;
		int lineheight = (int)(win->height / distwall_orth);
		int line_start = -lineheight / 2 + win->height / 2;
		if (line_start < 0)
			line_start = 0;
		int	line_end = lineheight / 2 + win->height / 2;
		if (line_end >= win->height)
			line_end = win->height - 1;
		int color = 0xFFFFFF;
		if (hit_side == 1)
			color /= 2;
		put_row(win->img, x, line_start, line_end, color);
	}
	ms_lastframe = ms_frame;
	ms_frame = time(NULL);
	time_t frametime = (ms_frame - ms_lastframe) / 1000.0;
	//printf("%ld", 1.0 / frametime);
	mlx_put_image_to_window(win->mlx, win->win, win->img->img, 0, 0);
	player->moveSpeed = frametime * 5.0;
	player->rotSpeed = frametime * 3.0;
}

int	key_move(int keycode, t_window *win)
{
	t_vector	*coord;
	t_vector	*dir;
	t_player	*player;

	coord = &win->player.coord;
	dir = &win->player.dir;
	player = &win->player;
	printf("%d\n", keycode);
	if (keycode == KEY_W)
	{
		if (Worldmap[(int)(coord->x + dir->y * player->moveSpeed)][(int)coord->y] == 0)
			coord->x += dir->x * player->moveSpeed;
		if (Worldmap[(int)coord->x][(int)(coord->y - dir->y * player->moveSpeed)] == 0)
			coord->y += dir->y * player->moveSpeed;
	}
}

int main()
{
	t_window	win;
	t_img		img;


	win.width = 800;
	win.height = 600;
	win.mlx	= mlx_init();
	win.win = mlx_new_window(win.mlx, win.width, win.height, "Cub3d v.0");
	img.img = mlx_new_image(win.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	win.img = &img;
	win.player.coord.x = 22;
	win.player.coord.y = 12;
	win.player.dir.x = -1;
	win.player.dir.y = 0;
	mlx_loop_hook(win.mlx, render_engine, &win);
	mlx_key_hook(win.mlx, key_move, &win);
	#ifdef DEBUG
	//mlx_key_hook(win, keyboard_test, mlx);
	#endif
	mlx_loop(win.mlx);
}