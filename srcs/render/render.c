/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:38:38 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/18 14:12:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "structs/t_img.h"
#include "structs/t_coord.h"
#include "structs/t_mouse.h"
#include "mlx_utils.h" // for img_pixel_put function
#include "img.h" // for mlx_img_to_bmp function
#include "render.h" // for circle pix structs
#include "player.h" // for player_pos function
#include "wall_render.h" // for projection function

void	put_square(t_img *img, t_square square)
{
	int printed_x;
	int printed_y;

	printed_x = -1;
	while (++printed_x < square.size)
	{
		printed_y = -1;
		while (++printed_y < square.size)
		{
			if (square.x + printed_x <= img->width
			&& square.y + printed_y <= img->height)
				img_pixel_put(img, square.x + printed_x,
				square.y + printed_y, square.color);
		}
	}
}

void	bresen_circle_point(t_img *img, t_circle c, int x, int y)
{
	img_pixel_put (img, c.x + x, c.y + y, c.color);
	img_pixel_put (img, c.x - x, c.y + y, c.color);
	img_pixel_put (img, c.x + x, c.y - y, c.color);
	img_pixel_put (img, c.x - x, c.y - y, c.color);
	img_pixel_put (img, c.x + y, c.y + x, c.color);
	img_pixel_put (img, c.x - y, c.y + x, c.color);
	img_pixel_put (img, c.x + y, c.y - x, c.color);
	img_pixel_put (img, c.x - y, c.y - x, c.color);
}

void	set_extrem_pixels(t_img *img, t_circle c)
{
	img_pixel_put (img, c.x, c.y + c.radius, c.color);
	img_pixel_put (img, c.x, c.y - c.radius, c.color);
	img_pixel_put (img, c.x + c.radius, c.y, c.color);
	img_pixel_put (img, c.x - c.radius, c.y, c.color);
}

void bresen_circle (t_img *img, t_circle c)
{
	int 		f;
	t_int_coord	ddF;
	t_int_coord	pix;

	f = 1 - c.radius;
	ddF.x = 1;
	ddF.y = -2 * c.radius;
	pix.x = 0;
	pix.y = c.radius;
	set_extrem_pixels(img, c);
	while (pix.x < pix.y)
	{
		if (f >= 0)
		{
			pix.y--;
			ddF.y += 2;
			f += ddF.y;
		}
		pix.x++;
		ddF.x += 2;
		f += ddF.x;
		bresen_circle_point(img, c, pix.x, pix.y);
	}
}

void	put_map_line(t_map map, int y)
{
	int 		x;
	t_square	grid_sq;

	grid_sq.y = y * TILE_SIZE;
	grid_sq.size = TILE_SIZE;
	x = -1;
	while (++x < map.x)
	{
		grid_sq.x = x * TILE_SIZE;
		if (map.grid[x][y] == '1')
			grid_sq.color = 0;
		else if (map.grid[x][y] == ' ')
			grid_sq.color = 0x1487DE;
		else
			grid_sq.color = 0x7FFFFFFF;
		put_square(map.img, grid_sq);
	}
}

int	map_drawer(t_map map)
{
	int	y;

	y = -1;
	while (++y < map.y)
	{
		put_map_line(map, y);
	}
	return (0);
}

void draw_player_pos(t_map map, t_player player)
{
	t_circle	player_c;
	int 		i;
	i = 0;

	player_c.x =  player.x * TILE_SIZE;
	player_c.y =  player.y * TILE_SIZE;
	player_c.radius = TILE_SIZE/4;
	player_c.color = 0xFF0000;
	bresen_circle(map.img, player_c);
	while (i <= TILE_SIZE / 2)
	{
		img_pixel_put(map.img, player_c.x + cos(player.rot_angl) * i, player_c.y + sin(player.rot_angl) * i, 0x00FF00);
		i++;
	}
}

void ray_drawer(t_map map, t_ray ray)
{
	int		i;
	double	x;
	double	y;

	x = ray.o_x * TILE_SIZE;
	y = ray.o_y * TILE_SIZE;
	i = 0;
	while (i < ray.distance * TILE_SIZE)
	{
		img_pixel_put(map.img, x + cos(ray.rayAngle) * i, y + + sin(ray.rayAngle) * i, 0x0000FF);
		i++;
	}
	
}

#include <stdio.h>

void mouse_move(t_window win, t_mouse *mouse)
{
	int x;
	int y;
	int	new_xvel;

	mlx_mouse_get_pos(win.mlx, win.win, &x, &y);
	new_xvel = (x - (win.width/2)) * 2;
	if (new_xvel == 0)
	{
		if (mouse->x_vel > 0)
			mouse->x_vel /= 2;
		else if (mouse->x_vel < 0)
			mouse->x_vel /= 2;
	}
	mouse->x_vel += new_xvel;
	if (mouse->x_vel > 10)
		mouse->x_vel = 10;
	if (mouse->x_vel < -10)
		mouse->x_vel = -10;
}

void map_process(t_window win, t_ray **rays){
	int		i;
	t_coord	orig;
	t_game	*game;

	game = &win.game;
	if (game->flags.showMap)
	{
		map_drawer(game->map);
		i = -1;
		while (++i < win.width)
			ray_drawer(game->map, *rays[i]);
		draw_player_pos(game->map, game->player);
		orig.x = game->frames.f1->width - game->map.img->width - 16;
		orig.y = game->frames.f1->height - game->map.img->height - 16;
		putImgOnImg(*game->map.img, game->frames.f1, orig);
	}
}

void player_process(t_window *win)
{
	t_game	*game;

	game = &win->game;
	if (game->mouse.mouse_in && game->flags.mouseControl)
		{ 
			mouse_move(*win, &game->mouse);
			mlx_mouse_move(win->mlx, win->win, win->width / 2, win->height / 2);
		}
	player_pos(&game->player, game->map, game->mouse.x_vel);
}

void render_frame(t_window win, t_ray **rays)
{
	t_img	*swap;
	t_game	*game;

	game = &win.game;
	projection(game->frames.f1, rays, game->player.rot_angl, game->textures);
	map_process(win, rays);
	if (win.save_to_bmp == true)
	{
		mlx_img_to_bmp(*game->frames.f1);
		mlx_loop_end(win.mlx);
		return ;
	}
	mlx_put_image_to_window(win.mlx, win.win, game->frames.f1->ptr, 0, 0);
	swap = game->frames.f1;
	game->frames.f1 = game->frames.f2;
	game->frames.f2 = swap;
}