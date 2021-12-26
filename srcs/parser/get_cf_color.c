/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cf_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:45:08 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 14:44:28 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../libs/libft/includes/libft.h"
#include "error_code.h"
#include "color_utils.h"
#include "parser.h"

static int	color_parser(char *rgb_line)
{
	int		color[3];
	int		size;
	char	**txt_color;
	int		i;

	txt_color = ft_split(rgb_line, ',');
	if (txt_color == NULL)
		return (MALLOC_ERROR);
	size = check_parameter_nbr(ft_split_size(txt_color), 3);
	if (size != 3)
	{
		ft_free_split(txt_color, size);
		return (size);
	}
	i = -1;
	while (++i < 3 && check_value(txt_color[i], false))
		color[i] = ft_atoi(txt_color[i]);
	ft_free_split(txt_color, size);
	if (i < 3)
		return (INCORRECT_VALUE);
	i = 0;
	while (i < 3)
		if (int_range(0, 255, color[i++]) == false)
			return (OUT_OF_RANGE);
	return (argb(0, color[0], color[1], color[2]));
}

int	get_cf_color(int *surface, bool *loaded, char **split)
{
	int	color;
	int	nbr_elem;

	if (*loaded)
		return (ALREADY_LOADED);
	nbr_elem = ft_split_size(split);
	if (nbr_elem < 2)
		return (NOT_ENOUGH);
	else if (nbr_elem > 2)
		return (TOO_MANY);
	color = color_parser(split[1]);
	*loaded = true;
	if (color >= 0)
		*surface = color;
	else
		return (color);
	return (0);
}
