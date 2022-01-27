/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:26:22 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 09:36:42 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs/t_map.h"
#include "structs/t_coord.h"
#include "map.h"
#include "error_code.h"

static bool	check_surrounding(t_map map, t_int_coord coord)
{
	if (coord.x == map.x - 1 || coord.y == map.y - 1
		|| coord.x == 0 || coord.y == 0)
		return (false);
	if (map.grid[coord.x - 1][coord.y - 1] == ' '
		|| map.grid[coord.x][coord.y - 1] == ' '
		|| map.grid[coord.x + 1][coord.y - 1] == ' '
		|| map.grid[coord.x + 1][coord.y] == ' '
		|| map.grid[coord.x + 1][coord.y + 1] == ' '
		|| map.grid[coord.x][coord.y + 1] == ' '
		|| map.grid[coord.x - 1][coord.y + 1] == ' '
		|| map.grid[coord.x - 1][coord.y] == ' ')
		return (false);
	return (true);
}

static bool	fill_space(t_map *map, t_int_coord c)
{
	bool	state;

	state = check_surrounding(*map, c);
	map->grid[c.x][c.y] = '1';
	if (state
		&& map->grid[c.x + 1][c.y] != ' ' && map->grid[c.x + 1][c.y] != '1')
		state = fill_space(map, (t_int_coord){c.x + 1, c.y});
	if (state
		&& map->grid[c.x][c.y + 1] != ' ' && map->grid[c.x][c.y + 1] != '1')
		state = fill_space(map, (t_int_coord){c.x, c.y + 1});
	if (state
		&& map->grid[c.x - 1][c.y] != ' ' && map->grid[c.x - 1][c.y] != '1')
		state = fill_space(map, (t_int_coord){c.x - 1, c.y});
	if (state
		&& map->grid[c.x][c.y - 1] != ' ' && map->grid[c.x][c.y - 1] != '1')
		state = fill_space(map, (t_int_coord){c.x, c.y - 1});
	return (state);
}

int	check_map_valid(t_map map)
{
	t_int_coord	c;
	t_map		map_cpy;
	bool		map_ok;

	if (map.x < 3 || map.y < 3)
		return (MAP_TOO_SMALL);
	map_cpy.x = map.x;
	map_cpy.y = map.y;
	map_cpy.grid = new_map_grid(map.x, map.y);
	cpy_map_grid(map.grid, map_cpy.grid, map.x, map.y);
	c.y = -1;
	map_ok = true;
	while (map_ok && ++c.y < map.y)
	{
		c.x = -1;
		while (map_ok && ++c.x < map.x)
			if (map_cpy.grid[c.x][c.y] != ' ' && map_cpy.grid[c.x][c.y] != '1')
				map_ok = fill_space(&map_cpy, c);
	}
	free_map_grid(map_cpy);
	if (!map_ok)
		return (MAP_INCORRECT);
	return (0);
}

int	check_map_content(t_map map)
{
	int		x;
	int		y;
	bool	sprites;

	sprites = false;
	y = -1;
	while (++y < map.y)
	{
		x = -1;
		while (++x < map.x)
		{
			if (map.grid[x][y] != '0' && map.grid[x][y] != '1'
				&& map.grid[x][y] != '2' && map.grid[x][y] != ' '
				&& map.grid[x][y] != 'S' && map.grid[x][y] != 'N'
				&& map.grid[x][y] != 'E' && map.grid[x][y] != 'W')
				return (INCORRECT_VALUE);
			if (map.grid[x][y] == '2')
				sprites = true;
		}
	}
	if (sprites)
		return (1);
	return (0);
}
