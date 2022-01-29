/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:02:40 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PLAYER_H
# define T_PLAYER_H
# include "t_ray.h"

typedef struct s_player
{
	float	x;
	float	y;
	float	radius;
	float	turn_dir;
	float	straf_dir;
	float	walk_dir;
	float	rot_angl;
	float	movespeed;
	float	rot_speed;
	t_ray	**rays;
}				t_player;
#endif