/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_datas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:22:31 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:51:31 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error_code.h"
#include "exit.h"
#include "checker.h"
#include "mlx_utils.h"
#include "ray.h"

void	check_parsed_datas(t_window *win)
{
	int	error;

	error = check_map_valid(win->game.map);
	if (error < 0)
		error_exit(error, NULL, "Check map is valid", win);
	error = check_map_content(win->game.map);
	if (error < 0)
		error_exit(error, NULL, "Check map content", win);
	if (check_loaded_values(*win, error) < 0)
		error_exit(MISSING_VALUE, NULL, "Check loaded values", win);
	error = spawn_player(win->game.map, &win->game.player);
	if (error < 0)
		error_exit(error, NULL, "Get player Spawn", win);
	check_res(win->mlx, &win->width, &win->height);
	win->game.frames.f1 = new_image(win->mlx, win->width, win->height);
	if (!win->game.frames.f1)
		error_exit(MALLOC_ERROR, "Can\'t malloc frame f1", NULL, win);
	win->game.frames.f2 = new_image(win->mlx, win->width, win->height);
	if (!win->game.frames.f2)
		error_exit(MALLOC_ERROR, "Can\'t malloc frame f2", NULL, win);
	win->game.player.rays = malloc_rays(win->width);
	if (!win->game.player.rays)
		error_exit(MALLOC_ERROR, "Can\'t malloc rays", NULL, win);
}
