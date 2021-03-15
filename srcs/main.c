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
/*
int Worldmap[24][24] =
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

int Worldmap[10][10] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

typedef struct	s_intvec
{
	int	x;
	int	y;
}				t_intvec;

typedef struct	s_vector
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

t_vec	deltadist(t_vec ray)
{
	t_vec	delta;
	
	if (ray.y == 0)
		delta.x = 0;
	else if (ray.x == 0)
		delta.x = 1;
	else
		delta.x = fabs(1 / ray.x);
	if (ray.x == 0)
		delta.y = 0;
	else if (ray.y == 0)
		delta.y = 1;
	else
		delta.y = fabs(1 / ray.y);
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
	t_vec	coord;
	t_vec	dir;
	t_vec	camera;
	double		moveSpeed;
	double		rotSpeed;
}				t_player;

typedef struct	s_map
{
	int	lenght;
	int	width;
	int	***map;
}				t_map;

typedef struct s_window
{
	void		*mlx;
	void		*win;
	int			width;
	int			height;
	char		*title;
	t_img		*img;
	t_player	player;
	t_map		map;

}			t_window;

t_vec	compute_ray(t_player player, int x, int win_width)
{
	t_vec	ray;
	double		camx;

	camx = 2 * x / (double)win_width -1;
	ray.x = player.dir.x + player.camera.x * camx;
	ray.y = player.dir.y + player.camera.y * camx;
	return (ray);
}

t_intvec	compute_step(t_vec ray)
{
	t_intvec	step;

	if (ray.x < 0)
		step.x = -1;
	else
		step.x = 1;
	if (ray.y < 0)
		step.y = -1;
	else
		step.y = 1;
	return (step);	
}

t_vec	distside(t_vec ray, t_vec coord, t_intvec posmap, t_vec delta)
{
	t_vec	dist_to_side;

	if (ray.x < 0)
		dist_to_side.x = (coord.x - posmap.x ) * delta.x;
	else
		dist_to_side.x = (posmap.x + 1.0 - coord.x) * delta.x;
	if (ray.y < 0)
		dist_to_side.y = (coord.y - posmap.y) * delta.y;
	else
		dist_to_side.y = (posmap.y + 1.0 - coord.y) * delta.y;
}

void	put_line(t_window *win, double dist_perpwall, int x, int side)
{
	int	line_height;
	int	line_top;
	int	line_bot;
	int color;

	line_height = (int)(win->height / dist_perpwall);

	line_top = -line_height / 2 + win->height / 2;
	if (line_top < 0)
		line_top = 0;
	line_bot = line_height / 2 + win->height / 2;
	if (line_bot >= win->height)
		line_bot = win->height - 1;

	if (side == 0)
		color = 0xFFFFFF;
	else
		color = 0x7F7F7F;
	for (int y = 0; y < line_top; y++)
		img_pixel_put(win->img, x, y, 0X87CEEB);

	while (line_top <= line_bot)
	{
		img_pixel_put(win->img, x, line_top, color);
		line_top++;
	}
	
	for (int y = line_bot + 1; y < win->height; y++)
		img_pixel_put(win->img, x, y, 0X835C3B);
}

int	render_engine(t_window *win)
{
	t_player	*player;
	int			x;
	double		camx;
	t_vec		ray;
	t_intvec	map;
	t_vec		sideDist;
	t_vec		deltaDist;
	double		perpWallDist;
	t_intvec	step;
	bool		hit = false;
	int			side;

	x = 0;
	player = &win->player;
	while (x < win->width)
	{
		camx = 2* x / (double)win->width - 1;
		ray.x = player->dir.x + player->camera.x * camx;
		ray.y = player->dir.y + player->camera.y * camx;

		map.x = (int)player->coord.x;
		map.y = (int)player->coord.y;

		deltaDist = deltadist(ray);
		step = compute_step(ray);
		sideDist =  distside(ray, player->coord, map, deltaDist);
		hit = false;
		while (hit == false)
		{
			if (sideDist.x < sideDist.y)
			{
				sideDist.x += deltaDist.x;
				map.x += step.x;
				side = 0;
			}
			else 
			{
				sideDist.y += deltaDist.y;
				map.y += step.y;
				side = 1;
			}
			if (Worldmap[map.x][map.y] > 0)
				hit = true;
		}
		if (side == 0)
			perpWallDist = (map.x - player->coord.x + (1 - step.x) / 2) / ray.x;
		else
			perpWallDist = (map.y - player->coord.y + (1 - step.y) / 2) / ray.y;
		put_line(win, perpWallDist, x, side);
		x++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img->img, 0, 0);
}

#define MOVESP 1
#define ROTSP 0.25

int	key_move(int keycode, t_window *win)
{
	t_player	*player;
	double		olddirx;
	double		oldcamx;
	int			segfault;
	for (int x = 0; x < win->width; x++)
		for (int y = 0; y < win->height; y++)
			img_pixel_put(win->img, x, y, 0);

	player = &win->player;
	if (keycode == KEY_W)
	{
		if (Worldmap[(int)(player->coord.x + player->dir.x * MOVESP)][(int)(player->coord.y)] == 0)
			player->coord.x += player->dir.x * MOVESP;
		if (Worldmap[(int)player->coord.x][(int)(player->coord.y + player->dir.y * MOVESP)] == 0)
			player->coord.y += player->dir.y * MOVESP;
	}
	if (keycode == KEY_S)
	{
		if (Worldmap[(int)(player->coord.x - player->dir.x * MOVESP)][(int)(player->coord.y)] == 0)
			player->coord.x -= player->dir.x * MOVESP;
		if (Worldmap[(int)player->coord.x][(int)(player->coord.y - player->dir.y * MOVESP)] == 0)
			player->coord.y -= player->dir.y * MOVESP;
	}
	if (keycode == KEY_RIGHT)
	{
		olddirx = player->dir.x;
		player->dir.x = player->dir.x * cos(-ROTSP) - player->dir.y * sin(-ROTSP);
		player->dir.y = olddirx * sin(-ROTSP) + player->dir.y * cos(-ROTSP);
		oldcamx = player->camera.x;
		player->camera.x = player->camera.x * cos(-ROTSP) - player->camera.y * sin(-ROTSP);
		player->camera.y = oldcamx * sin(-ROTSP) + player->camera.y * cos(-ROTSP);
	}
	if (keycode == KEY_LEFT)
	{
		olddirx = player->dir.x;
		player->dir.x = player->dir.x * cos(ROTSP) - player->dir.y * sin(ROTSP);
		player->dir.y = olddirx * sin(ROTSP) + player->dir.y * cos(ROTSP);
		oldcamx = player->camera.x;
		player->camera.x = player->camera.x * cos(ROTSP) - player->camera.y * sin(ROTSP);
		player->camera.y = oldcamx * sin(ROTSP) + player->camera.y * cos(ROTSP);
	}
	if (keycode == KEY_NUM_4)
	{
		oldcamx = player->camera.x;
		player->camera.x = player->camera.x * cos(-ROTSP) - player->camera.y * sin(-ROTSP);
		player->camera.y = oldcamx * sin(-ROTSP) + player->camera.y * cos(-ROTSP);
	}
	if (keycode == KEY_NUM_6)
	{
		oldcamx = player->camera.x;
		player->camera.x = player->camera.x * cos(ROTSP) - player->camera.y * sin(ROTSP);
		player->camera.y = oldcamx * sin(ROTSP) + player->camera.y * cos(ROTSP);
	}
	if (keycode == KEY_NUM_1)
	{
		olddirx = player->dir.x;
		player->dir.x = player->dir.x * cos(-ROTSP) - player->dir.y * sin(-ROTSP);
		player->dir.y = olddirx * sin(-ROTSP) + player->dir.y * cos(-ROTSP);
	}
	if (keycode == KEY_NUM_3)
	{
		olddirx = player->dir.x;
		player->dir.x = player->dir.x * cos(ROTSP) - player->dir.y * sin(ROTSP);
		player->dir.y = olddirx * sin(ROTSP) + player->dir.y * cos(ROTSP);
	}
	/*
	** Retires le code dessous sale macaque, t'es capable de l'oublier et de pas comprendre pourquoi ça segfault comme un con
	*/
	if (keycode == KEY_ESC)
		segfault = Worldmap[9999999][99999999];
}

int main()
{
	t_window	win;
	t_img		img;


	win.width = 1280;
	win.height = 720;
	win.mlx	= mlx_init();
	win.win = mlx_new_window(win.mlx, win.width, win.height, "Cub3d v.0");
	img.img = mlx_new_image(win.mlx, win.width, win.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	win.img = &img;
	win.player.coord.x = 5;
	win.player.coord.y = 5;
	win.player.dir.x = -1;
	win.player.dir.y = 0;
	win.player.camera.x = 0;
	win.player.camera.y = 0.66;
	win.map.map = &Worldmap;
	win.map.lenght = 32;
	win.map.width = 32;
	mlx_loop_hook(win.mlx, render_engine, &win);
	mlx_key_hook(win.win, key_move, &win);
	#ifdef DEBUG
	//mlx_key_hook(win.win, keyboard_test, &win);
	#endif
	mlx_loop(win.mlx);
}