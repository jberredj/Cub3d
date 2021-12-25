/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:36:03 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:24:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_UTILS_H
# define MLX_UTILS_H
# include "structs/t_img.h"
# include "structs/t_coord.h"
# include "structs/t_window.h"
void	putImgOnImg(t_img toPut, t_img *dst, t_coord orig);
void	img_pixel_put(t_img *data, int x, int y, int color);
t_img	*new_image(void *mlx, int width, int height);
int		get_color_from_mlx_img(t_img img, int x, int y);
t_img	*new_image_from_file(void *mlx, char *filename);
void	free_img(void *mlx, t_img **img);
int		close_mlx(t_window *win);
void	init_win_struct(t_window *win, char *title);
#endif