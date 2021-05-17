/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:58:13 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/06 12:38:00 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

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
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) - (((color >> 16) & 0xFF) * shade);
	g = ((color >> 8) & 0xFF) - (((color >> 8) & 0xFF) * shade);
	b = (color & 0xFF) - ((color & 0xFF) * shade);
	return(r << 16 | g << 8 | b);
}

int	rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (r << 16 | g << 8 | b);
}