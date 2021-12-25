/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:01:03 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/19 12:24:17 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx_utils.h"
#include "color_utils.h"
#include "game_engine.h"

void	init_img_struct(t_img *img)
{
	img->addr = NULL;
	img->bits_per_pixel = 0;
	img->endian = 0;
	img->height = 0;
	img->line_length = 0;
	img->ptr = NULL;
	img->width = 0;
}

void putImgOnImg(t_img toPut, t_img *dst, t_coord orig)
{
	t_coord	cur;
	t_coord prt;
	int color;

	cur.x = orig.x;
	cur.y = orig.y;
	prt.y = -1;
	while (cur.y >= 0 && cur.y < dst->height && ++prt.y < toPut.height)
	{
		prt.x = -1;
		while (cur.x >= 0 && cur.x < dst->width && ++prt.x < toPut.width)
		{
			color =  blend_argb(get_color_from_mlx_img(toPut, prt.x, prt.y), get_color_from_mlx_img(*dst, cur.x + prt.x, cur.y + prt.y));
			// color = get_color_from_mlx_img(toPut, prt.x, prt.y);

			// if (color == 0)
			// 	color = addShade(get_color_from_mlx_img(*dst, cur.x + prt.x, cur.y + prt.y), 0.5);
			img_pixel_put(dst, cur.x + prt.x, cur.y + prt.y, color);
		}
	}
}