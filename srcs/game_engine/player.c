/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:39:46 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:45:33 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "structs/t_player.h"
#include "structs/t_map.h"
#include "qwerty.h"
#include "ray.h"
#include "bonus_define.h"

t_player	init_player(float x, float y, float radius, float angle)
{
	t_player	player;

	player.x = x;
	player.y = y;
	player.radius = radius;
	player.turn_dir = 0;
	player.walk_dir = 0;
	player.rot_angl = angle * (M_PI / 180);
	player.straf_dir = 0;
	player.movespeed = 0.2;
	player.rot_speed = 3 * (M_PI / 180);
	player.rays = NULL;
	return (player);
}

static void	player_straff(t_player *player, t_map map)
{
	float	movestep;
	float	new_x;
	float	new_y;

	if (player->straf_dir == 0)
		movestep = 0;
	else
		movestep = player->movespeed;
	new_x = player->x + cos(player->straf_dir + player->rot_angl) * movestep;
	new_y = player->y + sin(player->straf_dir + player->rot_angl) * movestep;
	if (!BONUS || ((int)(new_x) < map.x && (int)(new_x) >= 0
		&& map.grid[(int)(new_x)][(int)(player->y)] != '1'))
		player->x = new_x;
	if (!BONUS || ((int)(new_y) < map.y && (int)(new_y) >= 0 &&
		map.grid[(int)(player->x)][(int)(new_y)] != '1'))
		player->y = new_y;
}

void	player_pos(t_player *player, t_map map, int mouse_x_vel)
{
	float	movestep;
	float	new_x;
	float	new_y;

	player->rot_angl += (player->turn_dir
			+ (int)mouse_x_vel) * player->rot_speed;
	player->rot_angl = normalize_angle(player->rot_angl);
	movestep = player->walk_dir * player->movespeed;
	new_x = player->x + cos(player->rot_angl) * movestep;
	new_y = player->y + sin(player->rot_angl) * movestep;
	if (!BONUS || ((int)(new_x) < map.x && (int)(new_x) >= 0
		&& map.grid[(int)(new_x)][(int)(player->y)] != '1'))
		player->x = new_x;
	if (!BONUS || ((int)(new_y) < map.y && (int)(new_y) >= 0
		&& map.grid[(int)(player->x)][(int)(new_y)] != '1'))
		player->y = new_y;
	player_straff(player, map);
}

void	kp_player(int keycode, t_player *player)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		player->walk_dir = 1;
	if (keycode == KEY_DOWN || keycode == KEY_S)
		player->walk_dir = -1;
	if (keycode == KEY_LEFT)
		player->turn_dir = -1;
	if (keycode == KEY_RIGHT)
		player->turn_dir = 1;
	if (keycode == KEY_A)
		player->straf_dir = 270 * (M_PI / 180);
	if (keycode == KEY_D)
		player->straf_dir = 90 * (M_PI / 180);
}

void	kr_player(int keycode, t_player *player)
{
	if (keycode == KEY_UP || keycode == KEY_W)
		player->walk_dir = 0;
	if (keycode == KEY_DOWN || keycode == KEY_S)
		player->walk_dir = 0;
	if (keycode == KEY_LEFT)
		player->turn_dir = 0;
	if (keycode == KEY_RIGHT)
		player->turn_dir = 0;
	if (keycode == KEY_A || keycode == KEY_D)
		player->straf_dir = 0;
}
