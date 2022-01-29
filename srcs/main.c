/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddiakova <ddiakova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:17:30 by jberredj          #+#    #+#             */
/*   Updated: 2022/01/27 09:22:48 by ddiakova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/includes/libft.h"
#include "parser.h"
#include "game_engine.h"
#include "ray.h"
#include "mlx_utils.h"
#include "mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "exit.h"
#include "error_code.h"
#include "checker.h"

int	check_file(char *file)
{
	int		fd;
	char	*check_ext;

	check_ext = ft_strrchr(file, '.');
	if (check_ext == NULL)
		return (FILE_NOT_DOT_CUB);
	if (!ft_strnstr(check_ext, ".cub", ft_strlen(check_ext)))
		return (FILE_NOT_DOT_CUB);
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

int	parse_arg(int argc, char **argv)
{
	int	fd;

	if (argc < 2)
		return (NOT_ENOUGH);
	if (argc > 2)
		return (TOO_MANY);
	fd = check_file(argv[1]);
	return (fd);
}

int	args(int argc, char **argv, t_window *win)
{
	int	error;

	error = parse_arg(argc, argv);
	if (error >= 0)
		return (error);
	error_exit(error, NULL, "Argument parser", win);
	return (0);
}

int	main(int argc, char **argv)
{
	t_window	win;
	int			fd;

	init_win_struct(&win, "Cub3D");
	win.game = init_game_engine();
	fd = args(argc, argv, &win);
	parser(&win, fd);
	check_parsed_datas(&win);
	create_win(&win);
	mlx_loop(win.mlx);
	free_exit(&win);
	return (0);
}
