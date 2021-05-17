/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:36:01 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:37:06 by jberredj         ###   ########.fr       */
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

int texture_wall(t_img *frame, t_ray ray, t_print_pix prt, t_textures tex)
{
	t_img	*texture;
	t_coord	tex_coord;
	int color;

	color = 0;
	texture = NULL;
	if (ray.wasHitVertical && ray.rayRight)
		texture = tex.e_tex;
	else if (ray.wasHitVertical && !ray.rayRight)
		texture = tex.w_tex;
	else if (!ray.wasHitVertical && !ray.rayDown)
		texture = tex.n_tex;
	else if (!ray.wasHitVertical && ray.rayDown)
		texture = tex.s_tex;
	if (ray.wasHitVertical)
		tex_coord.x = (int)(ray.wallHitY * texture->width) % texture->width;
	else
		tex_coord.x = (int)(ray.wallHitX * texture->width) % texture->width;
	if (ray.stripHeight  > frame->height)
		tex_coord.y = (int)((texture->height * (prt.pix + ((ray.stripHeight  - frame->height) / 2))) / ray.stripHeight) % texture->height;
	else
		tex_coord.y = (int)((texture->height * prt.pix) / ray.stripHeight) % texture->height;
	color = get_color_from_mlx_img(*texture, tex_coord.x, tex_coord.y);
	img_pixel_put(frame, ray.raynbr, prt.up + prt.pix, color);
	return (0);
}

void strip(t_img *frame, t_ray ray, t_textures tex)
{
	int up;
	t_coord tex_coord;
	int pix;

	tex_coord.x = 0;
	tex_coord.y = 0;
	up = (frame->height / 2) - (ray.stripHeight / 2);
	if (up < 0)
		up = 0;
	pix = -1;
	while (++pix < up && up != 0)
		img_pixel_put(frame, ray.raynbr, pix, tex.c_color);
	pix = -1;
	while (++pix <= ray.stripHeight && pix < frame->height)
		texture_wall(frame, ray, (t_print_pix){pix, up}, tex);
	while (pix + up < frame->height)
	{
		img_pixel_put(frame, ray.raynbr, up + pix, tex.f_color);
		pix++;
	}
	if (ray.wasHitVertical)
		tex_coord.x = (int)(ray.wallHitY * tex.n_tex->width) % tex.n_tex->width;
	else
		tex_coord.x = (int)(ray.wallHitX * tex.n_tex->width) % tex.n_tex->width;
}

void projection(t_img *frame, t_ray **rays, double player_angle, t_textures tex)
{
	int i;
	double distanceProjPlane;
	double correcteddistance;

	distanceProjPlane = (frame->width / 2) /
						tan((FOV * (M_PI / 180)) / 2);
	i = 0;
	while (i < frame->width)
	{
		correcteddistance = rays[i]->distance *
							cos(player_angle - rays[i]->rayAngle);
		rays[i]->stripHeight = (TILE_SIZE_3D /
								(correcteddistance * TILE_SIZE_3D) *
								distanceProjPlane);
		strip(frame, *rays[i], tex);
		i++;
	}
}