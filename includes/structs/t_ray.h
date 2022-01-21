/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:39 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
# define T_RAY_H
# include <stdbool.h>

typedef struct s_ray
{
	float	ray_angle;
	int		ray_nbr;
	float	o_x;
	float	o_y;
	bool	ray_down;
	bool	ray_right;
	float	wall_hit_x;
	float	wall_hit_y;
	bool	was_hit_vertical;
	float	strip_height;
	float	distance;
	bool	to_render;
}				t_ray;
#endif