/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:36:01 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 02:47:33 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "structs/t_img.h"
#include "structs/t_ray.h"
#include "structs/t_coord.h"
#include "wall_render.h" // t_print_pix struct
#include "mlx_utils.h" // for get_color_from_mlx_img function
#include "player.h" // for FOV define

int	tex_coord_y(t_img *frame, t_ray ray, t_print_pix prt, t_img *texture)
{
	if (ray.strip_height > frame->height)
		return ((int)((texture->height
				* (prt.pix + ((ray.strip_height - frame->height) / 2)))
			/ ray.strip_height) % texture->height);
	return ((int)((texture->height * prt.pix)
		/ ray.strip_height) % texture->height);
}

int	texture_wall(t_img *frame, t_ray ray, t_print_pix prt, t_textures tex)
{
	t_img	*texture;
	t_coord	tex_coord;
	int		color;

	color = 0;
	texture = NULL;
	if (ray.was_hit_vertical && ray.ray_right)
		texture = tex.e_tex;
	else if (ray.was_hit_vertical && !ray.ray_right)
		texture = tex.w_tex;
	else if (!ray.was_hit_vertical && !ray.ray_down)
		texture = tex.n_tex;
	else if (!ray.was_hit_vertical && ray.ray_down)
		texture = tex.s_tex;
	if (ray.was_hit_vertical)
		tex_coord.x = (int)(ray.wall_hit_y * texture->width) % texture->width;
	else
		tex_coord.x = (int)(ray.wall_hit_x * texture->width) % texture->width;
	tex_coord.y = tex_coord_y(frame, ray, prt, texture);
	color = get_color_from_mlx_img(*texture, tex_coord.x, tex_coord.y);
	img_pixel_put(frame, ray.ray_nbr, prt.up + prt.pix, color);
	return (0);
}

void	strip(t_img *frame, t_ray ray, t_textures tex)
{
	int		up;
	t_coord	tex_coord;
	int		pix;

	tex_coord.x = 0;
	tex_coord.y = 0;
	up = (frame->height / 2) - (ray.strip_height / 2);
	if (up < 0)
		up = 0;
	pix = -1;
	while (++pix < up && up != 0)
		img_pixel_put(frame, ray.ray_nbr, pix, tex.c_color);
	pix = -1;
	while (++pix <= ray.strip_height && pix < frame->height)
		texture_wall(frame, ray, (t_print_pix){pix, up}, tex);
	while (pix + up < frame->height)
		img_pixel_put(frame, ray.ray_nbr, up + pix++, tex.f_color);
	if (ray.was_hit_vertical)
		tex_coord.x = (int)(ray.wall_hit_y * tex.n_tex->width)
			% tex.n_tex->width;
	else
		tex_coord.x = (int)(ray.wall_hit_x * tex.n_tex->width)
			% tex.n_tex->width;
}

void	projection(t_img *frame, t_ray **rays, double player_angle,
	t_textures tex)
{
	int		i;
	double	distance_proj_plane;
	double	corrected_distance;

	distance_proj_plane = (frame->width / 2)
		/ tan((FOV * (M_PI / 180)) / 2);
	i = 0;
	while (i < frame->width)
	{
		corrected_distance = rays[i]->distance
			* cos(player_angle - rays[i]->ray_angle);
		rays[i]->strip_height = (TILE_SIZE_3D
				/ (corrected_distance * TILE_SIZE_3D)
				* distance_proj_plane);
		strip(frame, *rays[i], tex);
		i++;
	}
}
