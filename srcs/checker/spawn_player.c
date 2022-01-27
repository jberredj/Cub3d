/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:24:07 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:51:38 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs/t_map.h"
#include "error_code.h"
#include "player.h"

static bool	update_pos(int *px, int *py, int x, int y)
{
	*px = x;
	*py = y;
	return (true);
}

static int	check_for_spawn(t_map map, int *px, int *py)
{
	int		x;
	int		y;
	bool	found;

	found = false;
	y = -1;
	while (++y < map.y)
	{
		x = -1;
		while (++x < map.x)
		{
			if (map.grid[x][y] == 'E' || map.grid[x][y] == 'N' ||
				map.grid[x][y] == 'W' || map.grid[x][y] == 'S')
			{
				if (found == false)
					found = update_pos(px, py, x, y);
				else
					return (ALREADY_LOADED);
			}
		}
	}
	if (found)
		return (0);
	else
		return (MISSING_VALUE);
}

int	spawn_player(t_map map, t_player *player)
{
	int	x;
	int	y;
	int	dir;
	int	error;

	error = check_for_spawn(map, &x, &y);
	if (error != 0)
		return (error);
	if (map.grid[x][y] == 'E')
		dir = 0;
	else if (map.grid[x][y] == 'N')
		dir = 270;
	else if (map.grid[x][y] == 'W')
		dir = 180;
	else
		dir = 90;
	*player = init_player(x + 0.5, y + 0.5, 3, dir);
	return (0);
}
