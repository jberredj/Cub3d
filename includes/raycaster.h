/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:34:58 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# include "structs/t_coord.h"
# include "structs/t_ray.h"
# include "structs/t_map.h"
# include "structs/t_player.h"
# ifndef RENDER_DISTANCE
#  define RENDER_DISTANCE 32
# endif

t_coord	wall_hit(int offset, t_coord step, t_coord nextHit, t_map map);
t_coord	horiz_inter(t_ray *ray, t_map map);
t_coord	verti_inter(t_ray *ray, t_map map);
float	dst_point(t_coord p1, t_coord p2);
void	nearest_point(t_ray *ray, t_coord h_inter, t_coord v_inter);
void	cast(t_ray *ray, t_map map);
void	raycaster(int width, t_player player, t_map map);
#endif