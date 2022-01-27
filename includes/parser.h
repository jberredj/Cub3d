/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:50:17 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 08:52:01 by ddiakova         ###   ########.fr       */
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
int		create_map_from_raw(t_map *map, char *raw);
int		parser(t_window *win, int fd);
int		check_for_spawn(t_map map, int *px, int *py);
int		spawn_player(t_map map, t_player *player);
bool	check_surrounding(t_map map, t_int_coord coord);
int		check_map_valid(t_map map);
int		get_cf_color(int *surface, bool *loaded, char **split);
int		get_texture(t_img **img_tex, char **split, void *mlx);
int		read_cub_file(t_window *win, int fd, char **raw_map);
int		res_parser(int *width, int *height, bool *loaded, char **line);
bool	check_value(char *str, bool point);
bool	int_range(int min, int max, int value);
int		check_parameter_nbr(int value, int expected);
int		parse_raw_map(char *line, char **rawmap);
#endif