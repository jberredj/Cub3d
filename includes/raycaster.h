/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:34:58 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 12:19:27 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# include "structs/t_coord.h"
# include "structs/t_ray.h"
# include "structs/t_map.h"
# include "structs/t_player.h"

t_coord	wallHit(int offset, t_coord step, t_coord nextHit, t_map map);
t_coord	horiz_inter(t_ray *ray, t_map map);
t_coord	verti_inter(t_ray *ray, t_map map);
double	dst_point(t_coord p1, t_coord p2);
void	nearest_point(t_ray *ray, t_coord h_inter, t_coord v_inter);
void	cast(t_ray *ray, t_map map);
t_ray	**raycaster(int width, t_player player, t_map map);
#endif