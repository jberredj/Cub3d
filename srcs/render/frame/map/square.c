/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 02:09:38 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:55:01 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_img.h"
#include "mlx_utils.h" 

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
