/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:46:54 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/20 15:35:38 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "structs/t_window.h"
#include "qwerty.h"
#include "player.h"
#include "bonus_define.h"

int	key_pressed(int keycode, t_window *win)
{
	kp_player(keycode, &win->game.player);
	if (keycode == KEY_ESC)
		mlx_loop_end(win->mlx);
	return (0);
}

int	key_released(int keycode, t_window *win)
{
	kr_player(keycode, &win->game.player);
	if (keycode == KEY_EQUAL && BONUS)
	{
		win->game.flags.mouse_control = !win->game.flags.mouse_control;
		mlx_mouse_move(win->mlx, win->win, win->width / 2, win->height / 2);
		win->game.mouse.x_vel = 0;
	}
	if (keycode == KEY_M && BONUS)
		win->game.flags.show_map = !win->game.flags.show_map;
	if (keycode == KEY_P && BONUS)
		win->game.flags.pause = !win->game.flags.pause;
	return (0);
}
