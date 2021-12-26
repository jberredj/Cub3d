/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_player.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:02:40 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:45:35 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_PLAYER_H
# define T_PLAYER_H
# include "t_ray.h"

typedef struct s_player
{
	double	x;
	double	y;
	double	radius;
	double	turn_dir;
	double	straf_dir;
	double	walk_dir;
	double	rot_angl;
	double	movespeed;
	double	rot_speed;
	t_ray	**rays;
}				t_player;
#endif