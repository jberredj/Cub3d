/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:26:34 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:50:02 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/libft/includes/libft.h"
#include "structs/t_window.h"
#include "error_code.h"
#include "parser.h"

static int	finish_read(int fd, int code)
{
	int		read_line;
	char	*line;

	read_line = 1;
	while (read_line)
	{
		read_line = get_next_line(fd, &line);
		free(line);
		line = NULL;
	}	
	return (code);
}

int	read_cub_file(t_window *win, int fd, char **raw_map)
{
	char	*line;
	int		read_line;
	int		error;
	bool	empty_in_map;

	read_line = 1;
	line = NULL;
	empty_in_map = false;
	while (read_line)
	{
		read_line = get_next_line(fd, &line);
		if (empty_in_map && *line != '\0')
			return (EMPTY_LINE_IN_MAP);
		if (read_line == -1)
			return (CANT_READ_FILE);
		if (*line != '\0')
			error = parser_selector(win, line, raw_map);
		else if (ft_strlen(*raw_map) > 1)
			empty_in_map = true;
		free(line);
		line = NULL;
		if (error < 0)
			return (finish_read(fd, error));
	}
	return (0);
}
