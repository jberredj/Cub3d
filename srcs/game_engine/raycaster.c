/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:34:39 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 12:28:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "player.h"
#include "game_engine.h"
#include "../libs/libft/includes/libft.h"
#include "ray.h"
#include "structs/t_ray.h"
#include "structs/t_coord.h"

t_coord wallHit(int offset, t_coord step, t_coord nextHit, t_map map)
{
	int x_offset;
	int y_offset;

	x_offset = 0;
	y_offset = 0;
	if (offset == 1)
		x_offset = 1;
	if (offset == 2)
		y_offset = 1;
	while ((nextHit.x - x_offset < map.x && nextHit.y - y_offset< map.y)
		&& (nextHit.x - x_offset >= 0 && nextHit.y - y_offset >= 0))
	{
		if (map.grid[(int)nextHit.x - x_offset][(int)nextHit.y - y_offset] == '1')
			return ((t_coord){nextHit.x, nextHit.y});
		else
		{
			nextHit.x += step.x;
			nextHit.y += step.y;
		}
	}
	return ((t_coord){nextHit.x, nextHit.y});
}


t_coord horiz_inter(t_ray *ray, t_map map)
{
	t_coord inter;
	t_coord	step;
	t_coord nextHit;
	int offset;

	inter.y = floor(ray->o_y / 1) * 1;
	if (ray->rayDown)
		inter.y += 1;
	inter.x = ray->o_x + ((inter.y - ray->o_y) / tan(ray->rayAngle));
	step.y = 1;
	if (!ray->rayDown)
		step.y *= -1;
	step.x = 1 / tan(ray->rayAngle);
	if ((!ray->rayRight && step.x > 0) || (ray->rayRight && step.x < 0))
		step.x *= -1;
	nextHit.x = inter.x;
	nextHit.y = inter.y;
	offset = 0;
	if (!ray->rayDown)
		offset = 2;
		//nextHit.y--;
	return (wallHit(offset, step, nextHit, map));
}

t_coord verti_inter(t_ray *ray, t_map map)
{
	t_coord inter;
	t_coord	step;
	t_coord nextHit;
	int offset;

	inter.x = floor(ray->o_x) / 1 * 1;
	if (ray->rayRight)
		inter.x += 1;
	inter.y = ray->o_y + (inter.x - ray->o_x) * tan(ray->rayAngle);
	step.x = 1;
	if (!ray->rayRight)
		step.x *= -1;
	step.y = 1 * tan(ray->rayAngle);
	if ((!ray->rayDown && step.y > 0) || (ray->rayDown && step.y < 0))
		step.y *= -1;
	nextHit.x = inter.x;
	nextHit.y = inter.y;
	offset = 0;
	if (!ray->rayRight)
		offset = 1;
	// 	nextHit.x--;
	return (wallHit(offset, step, nextHit, map));
}

double dst_point(t_coord p1, t_coord p2)
{
	return (sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y))));
}

void nearest_point(t_ray *ray, t_coord h_inter, t_coord v_inter)
{
	double	v_len;
	double	h_len;

	v_len = 0;
	h_len = 0;
	if (h_inter.x != -1)
		h_len = dst_point((t_coord){ray->o_x, ray->o_y}, h_inter);
	if (v_inter.x != -1)
		v_len = dst_point((t_coord){ray->o_x, ray->o_y}, v_inter);
	ray->wasHitVertical = false;
	if (h_len < v_len)
	{
		ray->distance = h_len;
		ray->wallHitX = h_inter.x;
		ray->wallHitY = h_inter.y;
	}
	else
	{
		ray->distance = v_len;
		ray->wallHitX = v_inter.x;
		ray->wallHitY = v_inter.y;
		ray->wasHitVertical = true;
	}
}

void cast(t_ray *ray, t_map map)
{
	t_coord	h_inter;
	t_coord v_inter;
	h_inter = horiz_inter(ray, map);
	v_inter = verti_inter(ray, map);
	nearest_point(ray, h_inter, v_inter);
}

void	raycaster(int width, t_player player, t_map map)
{
	double		corrAngle;
	t_ray		**list_ray;
	int 		i;

	list_ray = player.rays;
	i = 0;
	while (i < width)
	{
		corrAngle = player.rot_angl + atan((i - (width / 2)) /
					((width / 2) / tan((FOV  * (M_PI / 180))/ 2)));
		*list_ray[i] = set_ray(corrAngle, i, player.x, player.y);
		cast(list_ray[i], map);
		i++;
	}
}
