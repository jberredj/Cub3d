/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:54:12 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:23:01 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libs/libft/includes/libft.h"
#include "structs/t_window.h"
#include "map.h"
#include "ray.h"
#include "mlx_utils.h"
#include "mlx.h"
#include "error_code.h"

void	free_exit(t_window *win)
{
	free_img(win->mlx, &win->game.map.img);
	free_img(win->mlx, &win->game.frames.f1);
	free_img(win->mlx, &win->game.frames.f2);
	free_img(win->mlx, &win->game.textures.n_tex);
	free_img(win->mlx, &win->game.textures.e_tex);
	free_img(win->mlx, &win->game.textures.s_tex);
	free_img(win->mlx, &win->game.textures.w_tex);
	if (win->win)
		mlx_destroy_window(win->mlx, win->win);
	mlx_destroy_display(win->mlx);
	free(win->mlx);
	free_map_grid(win->game.map);
	free_rays(win->game.player.rays, win->width);
}

void	print_code_desc_2(int code)
{
	if (code == FILE_NOT_DOT_CUB)
		ft_putstr_fd("File isn\'t a .cub file\n", 2);
	else if (code == FILE_IS_DIR)
		ft_putstr_fd("File is a directory\n", 2);
	else if (code == INCORRECT_ORDER)
		ft_putstr_fd("Incorrect order\n", 2);
	else if (code == EMPTY_LINE_IN_MAP)
		ft_putstr_fd("Found an empty line while parsing map\n", 2);
	else if (code == MAP_TOO_SMALL)
		ft_putstr_fd("The map is too small to be playable\n", 2);
	else
		ft_putstr_fd("Unknown error\n", 2);
}

void	print_code_desc(int code)
{
	if (code == MALLOC_ERROR)
		ft_putstr_fd("Malloc error\n", 2);
	else if (code == INCORRECT_VALUE)
		ft_putstr_fd("Incorrect value\n", 2);
	else if (code == OUT_OF_RANGE)
		ft_putstr_fd("Out of range value\n", 2);
	else if (code == NOT_ENOUGH)
		ft_putstr_fd("Not enough element\n", 2);
	else if (code == TOO_MANY)
		ft_putstr_fd("Too many element\n", 2);
	else if (code == ALREADY_LOADED)
		ft_putstr_fd("Value can only be declared once\n", 2);
	else if (code == CANT_OPEN_FILE)
		ft_putstr_fd("Can't open file\n", 2);
	else if (code == INVALID_PARAMETER)
		ft_putstr_fd("Invalide parameter\n", 2);
	else if (code == MISSING_VALUE)
		ft_putstr_fd("Missing value\n", 2);
	else if (code == MAP_INCORRECT)
		ft_putstr_fd("Map is incorrect\n", 2);
	else if (code == CANT_READ_FILE)
		ft_putstr_fd("Can\'t read file\n", 2);
	else
		print_code_desc_2(code);
}

void	error_exit(int code, char *reason, char *location, t_window *win)
{
	ft_putstr_fd("Error\nCode : ", 2);
	ft_putnbr_fd(-code, 2);
	ft_putstr_fd("\nCode description : ", 2);
	print_code_desc(code);
	if (reason != NULL)
	{
		ft_putstr_fd("Exit reason : ", 2);
		ft_putstr_fd(reason, 2);
	}
	if (location != NULL)
	{
		ft_putstr_fd("Exit location : ", 2);
		ft_putstr_fd(location, 2);
	}
	ft_putstr_fd("\n", 2);
	free_exit(win);
	exit(-code);
}
