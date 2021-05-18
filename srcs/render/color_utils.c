/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:58:13 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/18 15:15:20 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint8_t		get_a(int trgb)
{
	return (trgb & (0xFF << 24));
}

uint8_t		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

uint8_t		get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

uint8_t		get_b(int trgb)
{
	return (trgb & 0xFF);
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

int	argb(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int	blend_argb(int colora, int colorb)
{
	int new_color;
	int	alphaa;
	int	alphab;

	alphaa = 255 - get_a(colora);
	alphab = 255 - get_a(colorb);
	colora = argb(0, get_r(colora), get_g(colora), get_b(colora));
	colorb = argb(0, get_r(colorb), get_g(colorb), get_b(colorb));
	new_color = (colora * alphaa) + (colorb * alphab) *(1 - alphaa);
	return (new_color);
}