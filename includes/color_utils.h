/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 11:59:19 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/19 11:39:45 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H
# include <stdint.h>

int		addShade(int color, double shade);
int		argb(int a, int r, int g, int b);
int	blend_argb(int colora, int colorb);
#endif