/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:07:47 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:49:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "structs/t_ray.h"
double	normalizeAngle(double angle);
t_ray	*new_ray(double rayAngle, int col, double x, double y);
t_ray	set_ray(double rayAngle, int col, double x, double y);
void	free_rays(t_ray **rays, int nbr);
t_ray	**malloc_rays(int nbr);
void	reset_rays(t_ray **rays, int nbr);
#endif