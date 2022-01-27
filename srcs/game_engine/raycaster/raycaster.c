/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:34:39 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:40:16 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "player.h"
#include "../libs/libft/includes/libft.h"
#include "ray.h"
#include "structs/t_ray.h"
#include "raycaster.h"

void	cast(t_ray *ray, t_map map)
{
	t_coord	h_inter;
	t_coord	v_inter;

	h_inter = horiz_inter(ray, map);
	v_inter = verti_inter(ray, map);
	nearest_point(ray, h_inter, v_inter);
	if (ray->wall_hit_y < 0.0 || ray->wall_hit_y > map.y
		|| ray->wall_hit_x < 0.0 || ray->wall_hit_x > map.x
		|| ray->distance > RENDER_DISTANCE)
		ray->to_render = false;
}

void	raycaster(int width, t_player player, t_map map)
{
	float	corr_angle;
	t_ray	**list_ray;
	int		i;

	list_ray = player.rays;
	i = 0;
	while (i < width)
	{
		corr_angle = player.rot_angl + atanf((i - (width / 2))
				/ ((width / 2) / tanf((FOV * (M_PI / 180)) / 2)));
		*list_ray[i] = set_ray(corr_angle, i, player.x, player.y);
		cast(list_ray[i], map);
		i++;
	}
}
