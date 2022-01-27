/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 02:07:14 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 10:06:41 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "structs/t_img.h"
#include "structs/t_coord.h"
#include "map.h"
#include "mlx_utils.h"
#include "render.h"

void	draw_player_pos(t_map map, t_player player)
{
	t_circle	player_c;
	int			i;

	i = 0;
	player_c.x = player.x * TILE_SIZE;
	player_c.y = player.y * TILE_SIZE;
	player_c.radius = TILE_SIZE / 4;
	player_c.color = 0xFF0000;
	bresen_circle(map.img, player_c);
	while (i <= TILE_SIZE / 2)
	{
		img_pixel_put(map.img, player_c.x + cos(player.rot_angl) * i,
			player_c.y + sin(player.rot_angl) * i, 0x00FF00);
		i++;
	}
}

void	ray_drawer(t_map map, t_ray ray)
{
	int		i;
	float	x;
	float	y;

	x = ray.o_x * TILE_SIZE;
	y = ray.o_y * TILE_SIZE;
	i = 0;
	while (i < ray.distance * TILE_SIZE)
	{
		img_pixel_put(map.img, x + cos(ray.ray_angle) * i,
			y + sin(ray.ray_angle) * i, 0x0000FF);
		i++;
	}
}

void	put_map_line(t_map map, int y)
{
	int			x;
	t_square	grid_sq;

	grid_sq.y = y * TILE_SIZE;
	grid_sq.size = TILE_SIZE;
	x = -1;
	while (++x < map.x)
	{
		grid_sq.x = x * TILE_SIZE;
		if (map.grid[x][y] == '1')
			grid_sq.color = 0x7F000000;
		else if (map.grid[x][y] == ' ')
			grid_sq.color = 0xFF000000;
		else
			grid_sq.color = 0x00FFFFFF;
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

void	map_process(t_window win, t_ray **rays)
{
	int		i;
	t_coord	orig;
	t_game	*game;

	game = &win.game;
	if (game->flags.show_map)
	{
		map_drawer(game->map);
		i = -1;
		while (++i < win.width)
			ray_drawer(game->map, *rays[i]);
		draw_player_pos(game->map, game->player);
		orig.x = game->frames.f1->width - game->map.img->width - 16;
		orig.y = game->frames.f1->height - game->map.img->height - 16;
		put_img_on_img(*game->map.img, game->frames.f1, orig);
	}
}
