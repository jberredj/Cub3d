/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:45:11 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 13:59:15 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "structs/t_map.h"
# include "structs/t_player.h"
# include "structs/t_map.h"
# include "structs/t_img.h"
# include "structs/t_window.h"
# ifndef TILE_SIZE
#  define TILE_SIZE 4
# endif

void	draw_player_pos(t_map map, t_player player);
int		map_drawer(t_map map);
t_img	*new_image(void *mlx, int width, int height);
void	ray_drawer(t_map map, t_ray ray);
void	img_pixel_put(t_img *data, int x, int y, int color);
void	render_frame(t_window win, t_ray **rays);
void	player_process(t_window *win);
#endif