/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:44:59 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 02:51:05 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <X11/X.h>
#include "mlx.h"
#include "structs/t_window.h"
#include "game_engine.h"
#include "keyboard.h"
#include "mouse.h"

int	close_mlx(t_window *win)
{
	mlx_loop_end(win->mlx);
	return (0);
}

void	create_win(t_window *win)
{
	win->win = mlx_new_window(win->mlx, win->width, win->height,
			win->title);
	mlx_hook(win->win, ClientMessage, KeyPressMask, close_mlx, win);
	mlx_hook(win->win, KeyPress, KeyPressMask, key_pressed, win);
	mlx_hook(win->win, KeyRelease, KeyReleaseMask, key_released, win);
	mlx_hook(win->win, EnterNotify, EnterWindowMask, mouse_in, win);
	mlx_hook(win->win, LeaveNotify, LeaveWindowMask, mouse_out, win);
	mlx_loop_hook(win->mlx, game_loop, win);
}

void	init_win_struct(t_window *win, char *title)
{
	win->height = 0;
	win->load_res = false;
	win->mlx = mlx_init();
	win->title = title;
	win->width = 0;
	win->win = NULL;
}
