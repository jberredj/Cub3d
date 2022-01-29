/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_game.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:48:45 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:43:44 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_GAME_H
# define T_GAME_H
# include "t_mouse.h"
# include "t_flags.h"
# include "t_img.h"
# include "t_player.h"
# include "t_map.h"

typedef struct s_game
{
	t_mouse		mouse;
	t_flags		flags;
	t_textures	textures;
	t_frames	frames;
	t_player	player;
	t_map		map;
}				t_game;
#endif