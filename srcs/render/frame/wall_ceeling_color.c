/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ceeling_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:41:28 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:57:45 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_utils.h"

int	floor_color(int color, int up, int pix, int height)
{
	return (add_shade(color, 0.5 - (float)(((up + pix) - height / 2))
		/ (height - (height / 2))));
}

int	ceeling_color(int color, int pix, int height)
{
	float	shade;

	shade = -0.5 + (float)(((pix) - 0))
		/ ((height / 2) - (0));
	if (shade < 0.0)
		shade = 0.0;
	return (add_shade(color, shade));
}
