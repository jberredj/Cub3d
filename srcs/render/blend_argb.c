/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_argb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 01:58:50 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:23:56 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color_utils.h"

typedef struct s_argb
{
	int	a;
	int	r;
	int	g;
	int	b;
}			t_argb;

int	argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	blend_argb(int colora, int colorb)
{
	t_argb	ca;
	t_argb	cb;
	t_argb	c_out;

	ca.a = 255 - get_a(colora);
	ca.r = get_r(colora);
	ca.g = get_g(colora);
	ca.b = get_b(colora);
	cb.a = 255 - get_a(colorb);
	cb.r = get_r(colorb);
	cb.g = get_g(colorb);
	cb.b = get_b(colorb);
	if (ca.a == 0 && cb.b == 0)
		return (0xFF000000);
	c_out.a = ca.a + (cb.a * (255 - ca.a) / 255);
	c_out.r = (ca.r * ca.a + cb.r * cb.a * (255 - ca.a) / 255) / c_out.a;
	c_out.g = (ca.g * ca.a + cb.g * cb.a * (255 - ca.a) / 255) / c_out.a;
	c_out.b = (ca.b * ca.a + cb.b * cb.a * (255 - ca.a) / 255) / c_out.a;
	c_out.a = 255 - c_out.a;
	return (argb(c_out.a, c_out.r, c_out.g, c_out.b));
}
