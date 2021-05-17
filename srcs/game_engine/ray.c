/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:33:37 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:44:20 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "../libs/libft/includes/libft.h"
#include "structs/t_ray.h"
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

double normalizeAngle(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

t_ray *new_ray(double rayAngle, int col, double x, double y)
{
	t_ray *ray;
	ray = malloc(sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ray->rayAngle = normalizeAngle(rayAngle);
	ray->rayDown = false;
	ray->rayRight = false;
	ray->o_x = x;
	ray->o_y = y;
	ray->raynbr = col;
	return (ray);
}

t_ray set_ray(double rayAngle, int col, double x, double y)
{
	t_ray ray;

	ray.rayAngle = normalizeAngle(rayAngle);
	ray.rayDown = false;
	ray.rayRight = false;
	if (ray.rayAngle > 0 && ray.rayAngle < M_PI)
		ray.rayDown = true;
	if (ray.rayAngle < (M_PI / 2) || ray.rayAngle > (1.5 * M_PI))
		ray.rayRight = true;
	ray.o_x = x;
	ray.o_y = y;
	ray.raynbr = col;
	return (ray);
}

t_ray	**malloc_rays(int nbr)
{
	int i;
	t_ray	**rays;

	rays = ft_calloc(nbr, sizeof(t_ray *));
	i = -1;
	while (++i < nbr)
		rays[i] = new_ray(0, 0, 0, 0);
	return (rays);
}

void	reset_rays(t_ray **rays, int nbr)
{
	int i;

	i = -1;
	while (++i < nbr)
		*rays[i] = set_ray(0, 0, 0, 0);
}

void free_rays(t_ray **rays, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		free(rays[i]);
	free(rays);
}