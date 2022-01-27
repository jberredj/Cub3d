/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 13:41:21 by ddiakova          #+#    #+#             */
/*   Updated: 2022/01/27 08:49:35 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../libs/libft/includes/ft_string.h"
#include "structs/t_img.h"
#include "error_code.h"
#include "mlx_utils.h"

static int	check_xpm_file(char *file)
{
	int		fd;
	char	*check_ext;

	check_ext = ft_strrchr(file, '.');
	if (check_ext == NULL)
		return (FILE_NOT_DOT_XPM);
	if (!ft_strnstr(check_ext, ".xpm", ft_strlen(check_ext)))
		return (FILE_NOT_DOT_XPM);
	fd = open(file, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (FILE_IS_DIR);
	}
	fd = open(file, O_RDONLY);
	if (fd != -1)
		return (fd);
	return (CANT_OPEN_FILE);
}

int	get_texture(t_img **img_tex, char **split, void *mlx)
{
	int		fd;
	int		nbr_elem;

	fd = 0;
	nbr_elem = 0;
	nbr_elem = ft_split_size(split);
	if (nbr_elem < 2)
		return (NOT_ENOUGH);
	else if (nbr_elem > 2)
		return (TOO_MANY);
	fd = check_xpm_file(split[1]);
	if (fd < 0)
		return (fd);
	else
		close(fd);
	if (*img_tex != NULL)
		return (ALREADY_LOADED);
	*img_tex = new_image_from_file(mlx, split[1]);
	if (img_tex == NULL)
		return (MALLOC_ERROR);
	return (0);
}
