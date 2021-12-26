/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 01:24:50 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:25:30 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_ray.h"

void	free_rays(t_ray **rays, int nbr)
{
	int	i;

	i = -1;
	if (rays != NULL)
	{
		while (++i < nbr)
			free(rays[i]);
		free(rays);
	}
}
