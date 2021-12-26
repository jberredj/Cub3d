/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 02:13:44 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 02:14:28 by jberredj         ###   ########.fr       */
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

void	mouse_move(t_window win, t_mouse *mouse)
{
	int	x;
	int	y;
	int	new_xvel;

	mlx_mouse_get_pos(win.mlx, win.win, &x, &y);
	new_xvel = (x - (win.width / 2)) * 2;
	if (new_xvel == 0)
	{
		if (mouse->x_vel > 0)
			mouse->x_vel /= 2;
		else if (mouse->x_vel < 0)
			mouse->x_vel /= 2;
	}
	mouse->x_vel += new_xvel;
	if (mouse->x_vel > 10)
		mouse->x_vel = 10;
	if (mouse->x_vel < -10)
		mouse->x_vel = -10;
}

void	player_process(t_window *win)
{
	t_game	*game;

	game = &win->game;
	if (game->mouse.mouse_in && game->flags.mouse_control)
	{
		mouse_move(*win, &game->mouse);
		mlx_mouse_move(win->mlx, win->win, win->width / 2, win->height / 2);
	}
	player_pos(&game->player, game->map, game->mouse.x_vel);
}
