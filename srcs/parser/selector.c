/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:30:48 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 13:53:31 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/libft/includes/libft.h"
#include "structs/t_window.h"
#include "error_code.h"
#include "parser.h"

static int	is_in(char *line, char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		if (ft_strncmp(line, list[i], ft_strlen(list[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	parameters_parser(t_window *win, char **split)
{
	if (ft_strncmp(split[0], "R", 2) == 0)
		return (res_parser(&win->width, &win->height, &win->load_res, split));
	if (ft_strncmp(split[0], "NO", 3) == 0)
		return (get_texture(&win->game.textures.n_tex, split, win->mlx));
	if (ft_strncmp(split[0], "EA", 3) == 0)
		return (get_texture(&win->game.textures.e_tex, split, win->mlx));
	if (ft_strncmp(split[0], "SO", 3) == 0)
		return (get_texture(&win->game.textures.s_tex, split, win->mlx));
	if (ft_strncmp(split[0], "WE", 3) == 0)
		return (get_texture(&win->game.textures.w_tex, split, win->mlx));
	if (ft_strncmp(split[0], "F", 2) == 0)
		return (get_cf_color(&win->game.textures.f_color,
				&win->game.textures.f_loaded, split));
	if (ft_strncmp(split[0], "C", 2) == 0)
		return (get_cf_color(&win->game.textures.c_color,
				&win->game.textures.c_loaded, split));
	return (INVALID_PARAMETER);
}

int	parser_selector(t_window *win, char *line, char **rawmap)
{
	char	**split;
	int		error;

	if (is_in(line,
			(char *[]){"R", "NO", "SO", "WE", "EA", "S", "F", "C", NULL}))
	{
		if (ft_strlen(*rawmap) == 1)
		{
			split = NULL;
			split = ft_split(line, ' ');
			if (split == NULL)
				return (MALLOC_ERROR);
			error = parameters_parser(win, split);
			ft_free_split(split, ft_split_size(split));
		}
		else
			return (INCORRECT_ORDER);
	}
	else
		error = parse_raw_map(line, rawmap);
	return (error);
}
