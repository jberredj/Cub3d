/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:38:38 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 08:57:30 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "structs/t_img.h"
#include "structs/t_coord.h"
#include "structs/t_mouse.h"
#include "mlx_utils.h"
#include "render.h"
#include "player.h"
#include "wall_render.h"

void	render_frame(t_window win, t_ray **rays)
{
	t_img	*swap;
	t_game	*game;

	game = &win.game;
	projection(game->frames.f1, rays, game->player.rot_angl, game->textures);
	map_process(win, rays);
	mlx_put_image_to_window(win.mlx, win.win, game->frames.f1->ptr, 0, 0);
	swap = game->frames.f1;
	game->frames.f1 = game->frames.f2;
	game->frames.f2 = swap;
}
