/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:43:51 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/20 17:47:31 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# ifndef TILE_SIZE
#  define TILE_SIZE 4
# endif
# include "structs/t_map.h"

void	init_map_struct(t_map *map);
int		**new_map_grid(int x, int y);
void	cpy_map_grid(int **src, int **dest, int maxx, int maxy);
void	free_map_grid(t_map	map);
bool	is_in_map(int x, int y, t_map map);
#endif