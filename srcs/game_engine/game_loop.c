/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:52:28 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 10:07:06 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "mlx.h"
#include "map.h"
#include "structs/t_game.h"
#include "structs/t_window.h"
#include "player.h"
#include "render.h"
#include "ray.h"
#include "raycaster.h"

t_game	init_game_engine(void)
{
	t_game	game;

	init_map_struct(&game.map);
	game.player = init_player(0, 0, 3, 0);
	game.frames.f1 = NULL;
	game.frames.f2 = NULL;
	game.mouse.x_vel = 0;
	game.mouse.mouse_in = false;
	game.flags.mouse_control = false;
	game.flags.pause = false;
	game.flags.show_map = false;
	game.textures.c_color = 0;
	game.textures.c_loaded = false;
	game.textures.f_color = 0;
	game.textures.f_loaded = false;
	game.textures.e_tex = NULL;
	game.textures.n_tex = NULL;
	game.textures.s_tex = NULL;
	game.textures.w_tex = NULL;
	return (game);
}

int	game_loop(t_window *win)
{
	t_game	*game;

	game = &win->game;
	if (!game->flags.pause)
	{
		player_process(win);
		raycaster(win->width, game->player, game->map);
		render_frame(*win, game->player.rays);
		reset_rays(game->player.rays, win->width);
	}
	else
		mlx_string_put(win->mlx, win->win, win->width / 2 - 30,
			win->height / 2 - 10, 0, "PAUSE");
	return (0);
}
