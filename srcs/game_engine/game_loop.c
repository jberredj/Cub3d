/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:52:28 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 15:22:37 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "mlx.h"
#include "structs/t_game.h"
#include "structs/t_ray.h"
#include "structs/t_window.h"
#include "player.h" // for init_player function
#include "render.h" // for player_process function
#include "map.h" // for init_map_struct function
#include "ray.h" // for reset_rays function
#include "raycaster.h" // for raycaster function

t_game	init_game_engine(void)
{
	t_game	game;
	
	init_map_struct(&game.map);
	game.player = init_player(0, 0, 3, 0);
	game.frames.f1 = NULL;
	game.frames.f2 = NULL;
	game.mouse.x_vel = 0;
	game.mouse.mouse_in = false;
	game.flags.mouseControl = false;
	game.flags.pause = false;
	game.flags.showMap = false;
	game.textures.c_color = 0;
	game.textures.f_color = 0;
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
		mlx_string_put(win->mlx, win->win, win->width/2 - 30, win->height / 2 - 10, 0, "PAUSE");
	return (0);
}
