/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:45:11 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 10:06:16 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "structs/t_map.h"
# include "structs/t_player.h"
# include "structs/t_img.h"
# include "structs/t_window.h"

void	draw_player_pos(t_map map, t_player player);
int		map_drawer(t_map map);
t_img	*new_image(void *mlx, int width, int height);
void	ray_drawer(t_map map, t_ray ray);
void	img_pixel_put(t_img *data, int x, int y, int color);
void	render_frame(t_window win, t_ray **rays);
void	player_process(t_window *win);
void	bresen_circle(t_img *img, t_circle c);
void	put_square(t_img *img, t_square square);
void	map_process(t_window win, t_ray **rays);
#endif