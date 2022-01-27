/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map_from_raw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:56:58 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 09:48:26 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/libft/includes/ft_string.h"
#include "error_code.h"
#include "parser.h"
#include "map.h"

int	prepare_map_infos(t_map *map, char ***split, char *raw)
{
	*split = ft_split(raw, '\n');
	if (*split == NULL)
		return (MALLOC_ERROR);
	map->y = ft_split_size(*split);
	map->x = longuest_line(*split, map->y);
	map->grid = new_map_grid(map->x, map->y);
	if (map->grid == NULL)
	{
		ft_free_split(*split, ft_split_size(*split));
		return (MALLOC_ERROR);
	}
	return (0);
}

int	create_map_from_raw(t_map *map, char *raw)
{
	char	**split;
	int		x;
	int		y;
	size_t	len;

	if (prepare_map_infos(map, &split, raw))
		return (MALLOC_ERROR);
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		len = ft_strlen(split[y]);
		while (++x < map->x)
		{
			if (x < (int)len)
				map->grid[x][y] = (int)split[y][x];
			else
				map->grid[x][y] = ' ';
		}
	}
	ft_free_split(split, ft_split_size(split));
	return (0);
}
