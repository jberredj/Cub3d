/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cf_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:45:08 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:49:24 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../libs/libft/includes/libft.h"
#include "error_code.h"
#include "color_utils.h"
#include "parser.h"

static int	custom_check_parameter_nbr(char **split, char *line, int expected)
{
	int		size;
	int		comma_nbr;
	char	*comma_found;

	size = check_parameter_nbr(ft_split_size(split), expected);
	if (size != expected)
		return (size);
	comma_nbr = 0;
	comma_found = line;
	while (comma_found)
	{
		comma_found = ft_strchr(comma_found, ',');
		if (comma_found)
		{
			comma_nbr++;
			comma_found++;
		}
	}
	return (check_parameter_nbr(comma_nbr + 1, expected));
}

static int	color_parser(char *rgb_line)
{
	int		color[3];
	int		size;
	char	**txt_color;
	int		i;

	txt_color = ft_split(rgb_line, ',');
	if (txt_color == NULL)
		return (MALLOC_ERROR);
	size = custom_check_parameter_nbr(txt_color, rgb_line, 3);
	if (size != 3)
	{
		ft_free_split(txt_color, ft_split_size(txt_color));
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

static int	panic_combined_err(char **split, size_t size, size_t i)
{
	while (i < size)
	{
		free(split[i]);
		split[i] = NULL;
	}
	return (MALLOC_ERROR);
}

static int	combine_colors(char **split, size_t size)
{
	size_t	i;
	char	*combined;
	char	*tmp;

	i = 1;
	combined = ft_strdup("");
	if (!combined)
		return (MALLOC_ERROR);
	while (i < size)
	{
		tmp = ft_strjoin(combined, split[i]);
		if (!tmp)
			return (panic_combined_err(split, size, i));
		free(combined);
		combined = tmp;
		free(split[i]);
		i++;
	}
	split[1] = combined;
	split[2] = NULL;
	return (0);
}

int	get_cf_color(int *surface, bool *loaded, char **split)
{
	int	color;
	int	nbr_elem;
	int	error;

	if (*loaded)
		return (ALREADY_LOADED);
	nbr_elem = ft_split_size(split);
	error = 0;
	if (nbr_elem < 2)
		return (NOT_ENOUGH);
	else if (nbr_elem > 2)
		error = combine_colors(split, nbr_elem);
	if (error)
		return (error);
	color = color_parser(split[1]);
	*loaded = true;
	if (color >= 0)
		*surface = color;
	else
		return (color);
	return (0);
}
