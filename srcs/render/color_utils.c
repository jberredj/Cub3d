/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:58:13 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 02:00:51 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

int	get_a(int trgb)
{
	return ((trgb & 0xFF000000) >> 24);
}

int	get_r(int trgb)
{
	return ((trgb & 0x00FF0000) >> 16);
}

int	get_g(int trgb)
{
	return ((trgb & 0x0000FF00) >> 8);
}

int	get_b(int trgb)
{
	return (trgb & 0x000000FF);
}

int	add_shade(int color, double shade)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = ((color >> 24) & 0xFF) - (((color >> 24) & 0xFF) * shade);
	r = ((color >> 16) & 0xFF) - (((color >> 16) & 0xFF) * shade);
	g = ((color >> 8) & 0xFF) - (((color >> 8) & 0xFF) * shade);
	b = (color & 0xFF) - ((color & 0xFF) * shade);
	return (a << 24 | r << 16 | g << 8 | b);
}
