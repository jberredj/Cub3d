/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:36:27 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/19 16:45:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "../libs/libft/includes/ft_to.h"
#include "error_code.h"
#include "parser.h"

int	res_parser(int *width, int *height, bool *loaded, char **line)
{
	int	nbr_elem;

	if (*loaded)
		return (ALREADY_LOADED);
	nbr_elem = ft_split_size(line);
	if (nbr_elem < 3)
		return (NOT_ENOUGH);
	else if (nbr_elem > 3)
		return (TOO_MANY);
	if (!check_value(line[1], false) || !check_value(line[2], false))
		return (INCORRECT_VALUE);
	*width = ft_atoi(line[1]);
	*height = ft_atoi(line[2]);
	if (*height <= 0 || *width <= 0)
		return (OUT_OF_RANGE);
	*loaded = true;
	return (0);
}
