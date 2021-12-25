/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:39:20 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 12:22:03 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_RENDER_H
# define WALL_RENDER_H
# include "structs/t_img.h"
# include "structs/t_ray.h"
# ifndef TILE_SIZE_3D
#  define TILE_SIZE_3D 32
# endif
typedef struct	s_print_pix
{
	int	pix;
	int up;
}				t_print_pix;
int texture_wall(t_img *frame, t_ray ray, t_print_pix prt, t_textures tex);
void strip(t_img *frame, t_ray ray, t_textures tex);
void projection(t_img *frame, t_ray **rays, double player_angle, t_textures tex);

#endif