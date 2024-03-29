/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 01:23:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_ray.h"
#include "ray.h"
#include "player.h"

t_ray	set_ray(float ray_angle, int col, float x, float y)
{
	t_ray	ray;

	ray.ray_angle = normalize_angle(ray_angle);
	ray.ray_down = false;
	ray.ray_right = false;
	if (ray.ray_angle > 0 && ray.ray_angle < M_PI)
		ray.ray_down = true;
	if (ray.ray_angle < (M_PI / 2) || ray.ray_angle > (1.5 * M_PI))
		ray.ray_right = true;
	ray.o_x = x;
	ray.o_y = y;
	ray.ray_nbr = col;
	ray.to_render = true;
	return (ray);
}

void	reset_rays(t_ray **rays, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		*rays[i] = set_ray(0, 0, 0, 0);
}
