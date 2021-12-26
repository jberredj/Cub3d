/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:38:38 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 02:50:27 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "structs/t_img.h"
#include "structs/t_coord.h"
#include "structs/t_mouse.h"
#include "mlx_utils.h" // for img_pixel_put function
#include "img.h" // for mlx_img_to_bmp function
#include "render.h" // for circle pix structs
#include "player.h" // for player_pos function
#include "wall_render.h" // for projection function
#include <stdio.h>

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
