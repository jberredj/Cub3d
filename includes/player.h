/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:41:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 15:17:52 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "structs/t_player.h"
# include "structs/t_map.h"
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# ifndef FOV
#  define FOV 60
# endif

t_player	init_player(double x, double y, double radius, double angle);
void player_pos(t_player *player, t_map map, int mouse_x_vel);
void		kp_player(int keycode, t_player *player);
void		kr_player(int keycode, t_player *player);
#endif