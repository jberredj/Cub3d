/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:50:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:19:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdbool.h>
# include <stdlib.h>
# include "structs/t_window.h"
# include "structs/t_map.h"
# include "structs/t_coord.h"

int		parser_selector(t_window *win, char *line, char **rawmap);
int		longuest_line(char **split, size_t size);
void	create_map_from_raw(t_map *map, char *raw);
void	parser(t_window *win, char *file);
int		check_for_spawn(t_map map, int *px, int *py);
int		spawn_player(t_map map, t_player *player);
bool	check_surrounding(t_map map, t_int_coord coord);
bool	fill_space(t_map *map, t_int_coord c);
int		check_map_valid(t_map map);
#endif