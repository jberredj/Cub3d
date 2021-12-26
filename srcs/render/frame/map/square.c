/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 02:09:38 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 02:16:41 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "structs/t_img.h"
#include "structs/t_coord.h"
#include "structs/t_mouse.h"
#include "mlx_utils.h" // for img_pixel_put function
#include "img.h" // for mlx_img_to_bmp function
#include "render.h" // for circle pix structs
#include "player.h" // for player_pos function
#include "wall_render.h" // for projection function

void	put_square(t_img *img, t_square square)
{
	int	printed_x;
	int	printed_y;

	printed_x = -1;
	while (++printed_x < square.size)
	{
		printed_y = -1;
		while (++printed_y < square.size)
		{
			if (square.x + printed_x <= img->width
				&& square.y + printed_y <= img->height)
				img_pixel_put(img, square.x + printed_x,
					square.y + printed_y, square.color);
		}
	}
}
