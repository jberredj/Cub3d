/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:49:03 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:43:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include "../libs/libft/includes/libft.h"

int	**new_map_grid(int x, int y)
{
	int **grid;
	int	i;

	grid = ft_calloc(x, sizeof(int *));
	i = -1;
	while (++i < x)
		grid[i] = ft_calloc(y, sizeof(int));
	return (grid);
}

void	init_map_struct(t_map *map)
{
	map->grid = NULL;
	map->img = NULL;
	map->x = 0;
	map->y = 0;
}

void	cpy_map_grid(int **src, int **dest, int maxx, int maxy)
{
	int x;
	int	y;

	x = -1;
	while (++x < maxx)
	{
		y = -1;
		while (++y < maxy)
			dest[x][y] = src[x][y];
	}
		
	
}

void	free_map_grid(t_map	map)
{
	int i;

	i = -1;
	while (++i < map.x)
		free(map.grid[i]);
	free(map.grid);
}