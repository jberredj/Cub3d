/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:17:30 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:47:42 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//username : tony.kino.3@gmail.com
//password : TxywqbRxCbKQ4SS

#include "../libs/libft/includes/ft_string.h"
#include "parser.h" // for parser function
#include "game_engine.h" // for create_win, free_exit and game_loop functions
#include "ray.h" // for malloc ray function
#include "mlx_utils.h" // for new_image and init_win_structs_functions
#include "mlx.h" // for libmlx functions
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	t_window	win;

	init_win_struct(&win, "Cub3D");
	if (argc > 2)
		if (ft_strncmp(argv[2], "--save", 6) == 0)
			win.save_to_bmp = true;
	win.game = init_game_engine();
	parser(&win, argv[1]);
	win.game.frames.f1 = new_image(win.mlx, win.width, win.height);
	win.game.frames.f2 = new_image(win.mlx, win.width, win.height);
	spawn_player(win.game.map, &win.game.player);
	win.game.player.rays = malloc_rays(win.width);
	if (check_map_valid(win.game.map) == 0)
		printf("Map is valid");
	else
		printf("Map is not valid");
	if (!win.save_to_bmp)
	{
		create_win(&win);
		mlx_loop(win.mlx);
	}
	else
		game_loop(&win);
	free_exit(&win);
	printf("Segmentation fault, en fait non.\n");
	exit(0);
}