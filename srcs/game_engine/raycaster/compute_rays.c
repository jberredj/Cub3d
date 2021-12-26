/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 01:37:58 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:48:04 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "player.h"
#include "game_engine.h"
#include "../libs/libft/includes/libft.h"
#include "ray.h"
#include "structs/t_ray.h"
#include "structs/t_coord.h"

t_coord	wall_hit(int offset, t_coord step, t_coord nextHit, t_map map)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	y_offset = 0;
	if (offset == 1)
		x_offset = 1;
	if (offset == 2)
		y_offset = 1;
	while ((nextHit.x - x_offset < map.x && nextHit.y - y_offset < map.y)
		&& (nextHit.x - x_offset >= 0 && nextHit.y - y_offset >= 0))
	{
		if (map.grid[(int)nextHit.x - x_offset][(int)nextHit.y - y_offset]
			== '1')
			return ((t_coord){nextHit.x, nextHit.y});
		else
		{
			nextHit.x += step.x;
			nextHit.y += step.y;
		}
	}
	return ((t_coord){nextHit.x, nextHit.y});
}

t_coord	horiz_inter(t_ray *ray, t_map map)
{
	t_coord	inter;
	t_coord	step;
	t_coord	next_hit;
	int		offset;

	inter.y = floor(ray->o_y / 1) * 1;
	if (ray->ray_down)
		inter.y += 1;
	inter.x = ray->o_x + ((inter.y - ray->o_y) / tan(ray->ray_angle));
	step.y = 1;
	if (!ray->ray_down)
		step.y *= -1;
	step.x = 1 / tan(ray->ray_angle);
	if ((!ray->ray_right && step.x > 0) || (ray->ray_right && step.x < 0))
		step.x *= -1;
	next_hit.x = inter.x;
	next_hit.y = inter.y;
	offset = 0;
	if (!ray->ray_down)
		offset = 2;
	return (wall_hit(offset, step, next_hit, map));
}

t_coord	verti_inter(t_ray *ray, t_map map)
{
	t_coord	inter;
	t_coord	step;
	t_coord	next_hit;
	int		offset;

	inter.x = floor(ray->o_x) / 1 * 1;
	if (ray->ray_right)
		inter.x += 1;
	inter.y = ray->o_y + (inter.x - ray->o_x) * tan(ray->ray_angle);
	step.x = 1;
	if (!ray->ray_right)
		step.x *= -1;
	step.y = 1 * tan(ray->ray_angle);
	if ((!ray->ray_down && step.y > 0) || (ray->ray_down && step.y < 0))
		step.y *= -1;
	next_hit.x = inter.x;
	next_hit.y = inter.y;
	offset = 0;
	if (!ray->ray_right)
		offset = 1;
	return (wall_hit(offset, step, next_hit, map));
}

double	dst_point(t_coord p1, t_coord p2)
{
	return (sqrt(((p2.x - p1.x) * (p2.x - p1.x))
			+ ((p2.y - p1.y) * (p2.y - p1.y))));
}

void	nearest_point(t_ray *ray, t_coord h_inter, t_coord v_inter)
{
	double	v_len;
	double	h_len;

	v_len = 0;
	h_len = 0;
	if (h_inter.x != -1)
		h_len = dst_point((t_coord){ray->o_x, ray->o_y}, h_inter);
	if (v_inter.x != -1)
		v_len = dst_point((t_coord){ray->o_x, ray->o_y}, v_inter);
	ray->was_hit_vertical = false;
	if (h_len < v_len)
	{
		ray->distance = h_len;
		ray->wall_hit_x = h_inter.x;
		ray->wall_hit_y = h_inter.y;
	}
	else
	{
		ray->distance = v_len;
		ray->wall_hit_x = v_inter.x;
		ray->wall_hit_y = v_inter.y;
		ray->was_hit_vertical = true;
	}
}
