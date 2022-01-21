/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:42:37 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_to.h"

float	ft_atof(const char *str)
{
	float	digit;
	float	decimal;
	size_t	len;

	digit = 0;
	decimal = 0;
	digit = (float)ft_atoi(str);
	while (*str != '\0' && *str != '.')
		str++;
	if (*str == '\0')
		return (digit);
	len = ft_strlen(str);
	decimal = (float)ft_atoi(str);
	while (len--)
		decimal /= 10;
	if (digit < 0)
		digit -= decimal;
	else
		digit += decimal;
	return (digit);
}
