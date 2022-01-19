/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:38:38 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/19 15:20:48 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../libs/libft/includes/libft.h"
#include "error_code.h"

bool	check_value(char *str, bool point)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
		{
			if (point == true && *str == '.')
			{
				str++;
				continue ;
			}
			return (false);
		}
		str++;
	}
	return (true);
}

bool	int_range(int min, int max, int value)
{
	if (value >= min && value <= max)
		return (true);
	return (false);
}

int	check_parameter_nbr(int value, int expected)
{
	if (value < expected)
		return (NOT_ENOUGH);
	else if (value > expected)
		return (TOO_MANY);
	return (value);
}

int	longuest_line(char **split, size_t size)
{
	int		i;
	size_t	longuest;
	size_t	current;

	longuest = 0;
	i = -1;
	while (++i < (int)size)
	{
		current = ft_strlen(split[i]);
		if (current > longuest)
			longuest = current;
	}
	return (longuest);
}
