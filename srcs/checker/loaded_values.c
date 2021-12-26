/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loaded_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 14:31:08 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 14:32:28 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs/t_window.h"
#include "error_code.h"
#include "mlx.h"

int	check_loaded_values(t_window win, int need_sprites)
{
	if (need_sprites == 1 && !win.game.textures.sprites)
		return (MISSING_VALUE);
	if (!win.load_res || !win.game.textures.c_loaded
		|| !win.game.textures.f_loaded || !win.game.textures.c_loaded
		|| !win.game.textures.n_tex || !win.game.textures.s_tex
		|| !win.game.textures.e_tex || !win.game.textures.w_tex)
		return (MISSING_VALUE);
	return (0);
}

void	check_res(void *mlx, int *width, int *height)
{
	int	max_height;
	int	max_width;

	mlx_get_screen_size(mlx, &max_width, &max_height);
	if (*height > max_height)
		*height = max_height;
	if (*width > max_width)
		*width = max_width;
}
