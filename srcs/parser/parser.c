/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:14:46 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:49:46 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../libs/libft/includes/ft_string.h"
#include "structs/t_window.h"
#include "error_code.h"
#include "parser.h"
#include "map.h"
#include "mlx_utils.h"
#include "exit.h"

int	parser(t_window *win, int fd)
{
	char	*raw_map;
	int		error;

	raw_map = ft_calloc(2, sizeof(char));
	if (raw_map == NULL)
		return (MALLOC_ERROR);
	raw_map[0] = '\n';
	error = read_cub_file(win, fd, &raw_map);
	close(fd);
	if (error < 0)
	{
		free(raw_map);
		error_exit(error, NULL, "Cub file parser", win);
	}
	error = create_map_from_raw(&win->game.map, raw_map);
	free(raw_map);
	if (error < 0)
		error_exit(error, NULL, "Map loader", win);
	win->game.map.img = new_image(win->mlx, win->game.map.x * TILE_SIZE,
			win->game.map.y * TILE_SIZE);
	if (win->game.map.img == NULL)
		error_exit(MALLOC_ERROR, "Can\'t malloc map img",
			"Cub file parser", win);
	return (0);
}
