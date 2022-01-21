/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:07:47 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "structs/t_ray.h"

float	normalize_angle(float angle);
t_ray	*new_ray(float ray_angle, int col, float x, float y);
t_ray	set_ray(float ray_angle, int col, float x, float y);
void	free_rays(t_ray **rays, int nbr);
t_ray	**malloc_rays(int nbr);
void	reset_rays(t_ray **rays, int nbr);
#endif