/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:59:19 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 12:17:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H
# include <stdint.h>

uint8_t	get_r(int trgb);
uint8_t	get_g(int trgb);
uint8_t	get_b(int trgb);
int		addShade(int color, double shade);
int		rgb(uint8_t r, uint8_t g, uint8_t b);
#endif