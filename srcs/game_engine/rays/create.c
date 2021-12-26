/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 01:23:05 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:47:16 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/libft/includes/ft_string.h"
#include "structs/t_ray.h"
#include "ray.h"

t_ray	*new_ray(double ray_angle, int col, double x, double y)
{
	t_ray	*ray;

	ray = (t_ray *)ft_calloc(1, sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	ray->ray_angle = normalize_angle(ray_angle);
	ray->ray_down = false;
	ray->ray_right = false;
	ray->o_x = x;
	ray->o_y = y;
	ray->ray_nbr = col;
	return (ray);
}

void	fail_malloc_rays(t_ray **rays, int index_fail)
{
	int	i;

	i = -1;
	while (++i < index_fail)
	{
		free(rays[i]);
	}
}

t_ray	**malloc_rays(int nbr)
{
	int		i;
	t_ray	**rays;

	rays = ft_calloc(nbr, sizeof(t_ray *));
	if (!rays)
		return (NULL);
	i = -1;
	while (++i < nbr)
	{
		rays[i] = new_ray(0, 0, 0, 0);
		if (!rays[i])
		{
			fail_malloc_rays(rays, i);
			free(rays);
			return (NULL);
		}
	}
	return (rays);
}
