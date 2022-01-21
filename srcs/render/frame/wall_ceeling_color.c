/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_ceeling_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:41:28 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/21 14:23:50 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "structs/t_img.h"
#include "structs/t_ray.h"
#include "structs/t_coord.h"
#include "wall_render.h"
#include "mlx_utils.h"
#include "player.h"
#include "color_utils.h"
#include "raycaster.h"

int	floor_color(int color, int up, int pix, int height)
{
	return (add_shade(color, 0.5 - (float)(((up + pix) - height / 2))
		/ (height - (height / 2))));
}

int	ceeling_color(int color, int pix, int height)
{
	float	shade;

	shade = -0.5 + (float)(((pix) - 0))
		/ ((height / 2) - (0));
	if (shade < 0.0)
		shade = 0.0;
	return (add_shade(color, shade));
}
