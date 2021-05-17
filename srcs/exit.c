/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:12 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:26:26 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs/t_window.h"
#include "map.h" // for free_map_grid function
#include "ray.h" // for free_rays function
#include "mlx_utils.h" // for free_img function
#include "mlx.h" // for libmlx functions

void free_exit(t_window *win)
{
	free_img(win->mlx, &win->game.map.img);
	free_img(win->mlx, &win->game.frames.f1);
	free_img(win->mlx, &win->game.frames.f2);
	free_img(win->mlx, &win->game.textures.n_tex);
	free_img(win->mlx, &win->game.textures.e_tex);
	free_img(win->mlx, &win->game.textures.s_tex);
	free_img(win->mlx, &win->game.textures.w_tex);
	if (!win->save_to_bmp)
		mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free_map_grid(win->game.map);
	free_rays(win->game.player.rays, win->width);
}