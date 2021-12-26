/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:39 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:48:19 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
# define T_RAY_H
# include <stdbool.h>

typedef struct s_ray
{
	double	ray_angle;
	int		ray_nbr;
	double	o_x;
	double	o_y;
	bool	ray_down;
	bool	ray_right;
	double	wall_hit_x;
	double	wall_hit_y;
	bool	was_hit_vertical;
	double	strip_height;
	double	distance;
}				t_ray;
#endif