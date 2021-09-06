/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:58:13 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/19 14:03:09 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

int		get_a(int trgb)
{
	return ((trgb & 0xFF000000) >> 24);
}

int		get_r(int trgb)
{
	return ((trgb & 0x00FF0000) >> 16);
}

int	get_g(int trgb)
{
	return ((trgb & 0x0000FF00) >> 8);
}

int		get_b(int trgb)
{
	return (trgb & 0x000000FF);
}
 
int addShade(int color, double shade)
{
	int a;
	int	r;
	int	g;
	int	b;

	a = ((color >> 24) & 0xFF) - (((color >> 24) & 0xFF) * shade);
	r = ((color >> 16) & 0xFF) - (((color >> 16) & 0xFF) * shade);
	g = ((color >> 8) & 0xFF) - (((color >> 8) & 0xFF) * shade);
	b = (color & 0xFF) - ((color & 0xFF) * shade);
	return(a << 24 | r << 16 | g << 8 | b);
}

int	argb(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

typedef	struct s_argb
{
	int a;
	int r;
	int g;
	int	b;
}			t_argb;


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
	// c_out.a = 255 - ca.a + (cb.a * (255 - ca.a) / 255);
	// c_out.r = (ca.r * ca.a / 255) + (cb.r * cb.a * (255 - ca.a) / (255*255));
	// c_out.g = (ca.g * ca.a / 255) + (cb.g * cb.a * (255 - ca.a) / (255*255));
	// c_out.b = (ca.g * ca.a / 255) + (cb.b * cb.a * (255 - ca.a) / (255*255));
	return (argb(c_out.a, c_out.r, c_out.g, c_out.b));
}