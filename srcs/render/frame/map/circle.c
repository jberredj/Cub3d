/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 02:09:05 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:53:36 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_img.h"
#include "structs/t_coord.h"
#include "mlx_utils.h"

static void	bresen_circle_point(t_img *img, t_circle c, int x, int y)
{
	img_pixel_put(img, c.x + x, c.y + y, c.color);
	img_pixel_put(img, c.x - x, c.y + y, c.color);
	img_pixel_put(img, c.x + x, c.y - y, c.color);
	img_pixel_put(img, c.x - x, c.y - y, c.color);
	img_pixel_put(img, c.x + y, c.y + x, c.color);
	img_pixel_put(img, c.x - y, c.y + x, c.color);
	img_pixel_put(img, c.x + y, c.y - x, c.color);
	img_pixel_put(img, c.x - y, c.y - x, c.color);
}

static void	set_extrem_pixels(t_img *img, t_circle c)
{
	img_pixel_put(img, c.x, c.y + c.radius, c.color);
	img_pixel_put(img, c.x, c.y - c.radius, c.color);
	img_pixel_put(img, c.x + c.radius, c.y, c.color);
	img_pixel_put(img, c.x - c.radius, c.y, c.color);
}

void	bresen_circle(t_img *img, t_circle c)
{
	int			f;
	t_int_coord	ddf;
	t_int_coord	pix;

	f = 1 - c.radius;
	ddf.x = 1;
	ddf.y = -2 * c.radius;
	pix.x = 0;
	pix.y = c.radius;
	set_extrem_pixels(img, c);
	while (pix.x < pix.y)
	{
		if (f >= 0)
		{
			pix.y--;
			ddf.y += 2;
			f += ddf.y;
		}
		pix.x++;
		ddf.x += 2;
		f += ddf.x;
		bresen_circle_point(img, c, pix.x, pix.y);
	}
}
