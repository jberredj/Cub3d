/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:44:49 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/20 17:45:09 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "map.h"

bool	is_in_map(int x, int y, t_map map)
{
	if ((x >= 0 && x < map.x) && (y >= 0 && y < map.y))
		return (true);
	return (false);
}
