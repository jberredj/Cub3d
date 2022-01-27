/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:53:40 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:49:54 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/libft/includes/ft_string.h"
#include "error_code.h"

static char	*ft_strjoin_free(char *to_free, char *s2)
{
	char	*ret;

	ret = NULL;
	ret = ft_strjoin(to_free, s2);
	free(to_free);
	return (ret);
}

int	parse_raw_map(char *line, char **rawmap)
{
	char	*new_rawmap;

	new_rawmap = ft_strjoin_free(*rawmap, line);
	if (new_rawmap == NULL)
		return (MALLOC_ERROR);
	*rawmap = ft_strjoin_free(new_rawmap, "\n");
	if (*rawmap == NULL)
		return (MALLOC_ERROR);
	return (0);
}
