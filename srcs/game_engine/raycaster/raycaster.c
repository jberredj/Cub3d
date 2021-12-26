/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:34:39 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:40:11 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "player.h"
#include "game_engine.h"
#include "../libs/libft/includes/libft.h"
#include "ray.h"
#include "structs/t_ray.h"
#include "structs/t_coord.h"
#include "raycaster.h"

void	cast(t_ray *ray, t_map map)
{
	t_coord	h_inter;
	t_coord	v_inter;

	h_inter = horiz_inter(ray, map);
	v_inter = verti_inter(ray, map);
	nearest_point(ray, h_inter, v_inter);
}

void	raycaster(int width, t_player player, t_map map)
{
	double	corr_angle;
	t_ray	**list_ray;
	int		i;

	list_ray = player.rays;
	i = 0;
	while (i < width)
	{
		corr_angle = player.rot_angl + atan((i - (width / 2))
				/ ((width / 2) / tan((FOV * (M_PI / 180)) / 2)));
		*list_ray[i] = set_ray(corr_angle, i, player.x, player.y);
		cast(list_ray[i], map);
		i++;
	}
}
