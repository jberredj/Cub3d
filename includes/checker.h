/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:25:32 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 08:52:22 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "structs/t_window.h"

void	check_parsed_datas(t_window *win);
void	check_res(void *mlx, int *width, int *height);
int		check_loaded_values(t_window win, int need_sprites);
int		spawn_player(t_map map, t_player *player);
int		check_map_valid(t_map map);
int		check_map_content(t_map map);
#endif