/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:50:43 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/18 17:10:49 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libs/libft/includes/libft.h"
#include "structs/t_window.h"
#include "structs/t_coord.h"
#include "color_utils.h"
#include "mlx_utils.h"
#include "mlx.h"
#include "map.h"
#include "player.h"
#include "error_code.h"
#include "img.h"
#include "exit.h"
#include "ray.h"

char	*ft_strjoin_free(char *to_free, char *s2)
{
	char *ret;

	ret = NULL;
	ret = ft_strjoin(to_free, s2);
	free(to_free);
	return (ret);
}

int	check_file_exist(char *file)
{
	int		fd;

	fd = open(file, O_DIRECTORY);
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
	fd = check_file_exist(split[1]);
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

bool	int_range(int min, int max, int value)
{
	if (value >= min && value <= max)
		return (true);
	return (false);
}

bool	check_value(char *str, bool point)
{
	if (str == NULL)
		return (false);
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-' && *str != '+')
		{
			if (point == true && *str == '.')
			{
				str++;
				continue ;
			}
			return (false);
		}
		str++;
	}
	return (true);
}

int	check_parameter_nbr(int value, int expected)
{
	if (value < expected)
		return (NOT_ENOUGH);
	else if (value > expected)
		return (TOO_MANY);
	return (value);
}

int	color_parser(char *rgb_line)
{
	int		color[3];
	int		size;
	char	**txt_color;
	int		i;

	txt_color = ft_split(rgb_line, ',');
	if (txt_color == NULL)
		return (MALLOC_ERROR);
	size = check_parameter_nbr(ft_split_size(txt_color), 3);
	if (size != 3)
	{
		ft_free_split(txt_color, size);
		return (size);
	}
	i = -1;
	while (++i < 3 && check_value(txt_color[i], false))
		color[i] = ft_atoi(txt_color[i]);
	ft_free_split(txt_color, size);
	if (i < 3)
		return (INCORRECT_VALUE);
	i = 0;
	while (i < 3)
		if (int_range(0, 255, color[i++]) == false)
			return (OUT_OF_RANGE);
	return (argb(0, color[0], color[1], color[2]));
}

int		get_cf_color(int *surface, bool* loaded, char **split)
{
	int color;
	int nbr_elem;

	if (*loaded)
		return (ALREADY_LOADED);
	nbr_elem = ft_split_size(split);
	if (nbr_elem < 2)
		return (NOT_ENOUGH);
	else if (nbr_elem > 2)
		return (TOO_MANY);
	color = color_parser(split[1]);
	*loaded = true;
	if (color >= 0)
		*surface = color;
	else
		return (color);
	return (0);
}

int	res_parser(int *width, int *height, bool *loaded, char **line)
{
	int	nbr_elem;

	if (*loaded)
		return (ALREADY_LOADED);
	nbr_elem = ft_split_size(line);
	if (nbr_elem < 3)
		return (NOT_ENOUGH);
	else if (nbr_elem > 3)
		return (TOO_MANY);
	if (!check_value(line[1], false) || !check_value(line[2], false))
		return (INCORRECT_VALUE);
	*width = ft_atoi(line[1]);
	*height = ft_atoi(line[2]);
	if (*height < 0 || *width < 0)
		return (OUT_OF_RANGE);
	*loaded = true;
	return (0);
}


int 	parameters_parser(t_window *win, char **split)
{
	if (ft_strncmp(split[0], "R", 1) == 0)
		return (res_parser(&win->width, &win->height, &win->load_res, split));
	if (ft_strncmp(split[0], "NO", 2) == 0)
		return (get_texture(&win->game.textures.n_tex, split, win->mlx));
	if (ft_strncmp(split[0], "EA", 2) == 0)
		return (get_texture(&win->game.textures.e_tex, split, win->mlx));
	if (ft_strncmp(split[0], "SO", 2) == 0)
		return (get_texture(&win->game.textures.s_tex, split, win->mlx));
	if (ft_strncmp(split[0], "WE", 2) == 0)
		return (get_texture(&win->game.textures.w_tex, split, win->mlx));
	if (ft_strncmp(split[0], "S", 1) == 0)
		return (get_texture(&win->game.textures.sprites, split, win->mlx));
	if (ft_strncmp(split[0], "F", 1) == 0)
		return (get_cf_color(&win->game.textures.f_color, &win->game.textures.f_loaded, split));
	if (ft_strncmp(split[0], "C", 1) == 0)
		return (get_cf_color(&win->game.textures.c_color, &win->game.textures.c_loaded, split));
	return (INVALID_PARAMETER);
}

int	is_in(char *line, char **list, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (ft_strncmp(line, list[i], ft_strlen(list[i])) == 0)
			return (1);
		i++;
	}
	return (0);
}

int parse_raw_map(char *line, char **rawmap)
{
	char	*new_rawmap;

	new_rawmap = ft_strjoin_free(*rawmap, line);
	if (new_rawmap == NULL)
		return (MALLOC_ERROR);
	*rawmap = ft_strjoin_free(new_rawmap, "\n");
	if (*rawmap == NULL)
		return (MALLOC_ERROR);
	return (0);
}

int	parser_selector(t_window *win, char *line, char **rawmap)
{
	char	**split;
	int 	error;

	if (is_in(line, (char *[]){"R", "NO", "SO", "WE", "EA", "S", "F", "C"}, 8))
	{
		if (ft_strlen(*rawmap) == 1)
		{
			split = NULL;
			split = ft_split(line, ' ');
			if (split == NULL)
				return (MALLOC_ERROR);
			error = parameters_parser(win, split);
			ft_free_split(split, ft_split_size(split));
		}
		else
			return (INCORRECT_ORDER);
	}
	else 
		error = parse_raw_map(line, rawmap);
	return (error);
}

int		longuest_line(char **split, size_t size)
{
	int i;
	size_t	longuest;
	size_t	current;

	longuest = 0;
	i = -1;
	while (++i < (int)size)
	{
		current = ft_strlen(split[i]);
		if (current > longuest)
			longuest = current;
	}
	return (longuest);
}

int	create_map_from_raw(t_map *map, char *raw)
{
	char	**split;
	int 	x;
	int		y;
	size_t	len;

	split = ft_split(raw, '\n');
	if (split == NULL)
		return (MALLOC_ERROR);
	map->y = ft_split_size(split);
	map->x = longuest_line(split, map->y);
	map->grid = new_map_grid(map->x, map->y);
	if (map->grid == NULL)
	{
		ft_free_split(split, ft_split_size(split));
		return (MALLOC_ERROR);
	}
	y = -1;
	while (++y < map->y)
	{
		x = -1;
		len = ft_strlen(split[y]);
		while (++x < map->x)
		{
			if (x < (int)len)
				map->grid[x][y] = (int)split[y][x];
			else
				map->grid[x][y] = ' ';
		}
	}
	ft_free_split(split, ft_split_size(split));
	return (0);
}

int	finish_read(int fd, int code)
{
	int		read_line;
	char	*line;

	read_line = 1;
	while (read_line)
	{
		read_line = get_next_line(fd, &line);
		free(line);
		line = NULL;
	}
	
	return (code);
}

int	read_cub_file(t_window *win, int fd, char **raw_map)
{
	char	*line;
	int		read_line;
	int 	error;
	bool	empty_in_map;

	read_line = 1;
	line = NULL;
	empty_in_map = false;
	while (read_line)
	{
		read_line = get_next_line(fd, &line);
		if (empty_in_map && *line != '\0')
			return (EMPTY_LINE_IN_MAP);
		if (read_line == -1)
			return (CANT_READ_FILE);
		if (*line != '\0')
			error = parser_selector(win, line, raw_map);
		else if (ft_strlen(*raw_map) > 1)
			empty_in_map = true;
		free(line);
		line = NULL;
		if (error < 0)
			return(finish_read(fd, error));
	}
	return (0);
}

#include <stdio.h>

int	parser(t_window *win, int fd)
{
	char	*raw_map;
	int 	error;

	raw_map = ft_calloc(2, sizeof(char));
	if (raw_map == NULL)
		return (MALLOC_ERROR);
	raw_map[0] = '\n';
	error = read_cub_file(win, fd, &raw_map);
	close(fd);
	if (error < 0)
	{
		free(raw_map);
		error_exit(error, NULL, "Cub file parser", win);
	}
	error = create_map_from_raw(&win->game.map, raw_map);
	free(raw_map);
	if (error < 0)
		error_exit(error, NULL, "Map loader", win);
	win->game.map.img = new_image(win->mlx, win->game.map.x * TILE_SIZE,
					win->game.map.y * TILE_SIZE);
	if (win->game.map.img == NULL)
		error_exit(MALLOC_ERROR, "Can\'t malloc map img", "Cub file parser", win);
	return (0);
}

int	check_for_spawn(t_map map, int *px, int *py)
{
	int		x;
	int		y;
	bool	found;

	found = false;
	y = -1;
	while (++y < map.y)
	{
		x = -1;
		while (++x < map.x)
		{
			if (map.grid[x][y] == 'E' || map.grid[x][y] == 'N' ||
				map.grid[x][y] == 'W' || map.grid[x][y] == 'S')
				{
					if (found == false)
					{
						found = true;
						*px = x;
						*py = y;
					}
					else
						return (ALREADY_LOADED);
				}
		}
	}
	if (found)
		return (0);
	else
		return (MISSING_VALUE);
}

int spawn_player(t_map map, t_player *player)
{
	int	x;
	int	y;
	int	dir;
	int	error;

	error = check_for_spawn(map, &x, &y);
	if (error != 0)
		return (error);
	if (map.grid[x][y] == 'E')
		dir = 0;
	else if (map.grid[x][y] == 'N')
		dir = 270;
	else if (map.grid[x][y] == 'W')
		dir = 180;
	else
		dir = 90;	
	*player = init_player(x + 0.5 , y + 0.5, 3, dir);
	return (0);
}

/*
** Check if the parsed map is valid
*/
bool	check_surrounding(t_map map, t_int_coord coord)
{
	if (coord.x == map.x - 1 || coord.y == map.y - 1
		|| coord.x == 0 || coord.y == 0)
		return (false);
	if (map.grid[coord.x - 1][coord.y - 1] == ' '
		|| map.grid[coord.x][coord.y - 1] == ' '
		|| map.grid[coord.x + 1][coord.y - 1] == ' '
		|| map.grid[coord.x + 1][coord.y] == ' '
		|| map.grid[coord.x + 1][coord.y + 1] == ' '
		|| map.grid[coord.x][coord.y + 1] == ' '
		|| map.grid[coord.x - 1][coord.y + 1] == ' '
		|| map.grid[coord.x - 1][coord.y] == ' ')
		return (false);
	return (true);
}

bool fill_space(t_map *map, t_int_coord c)
{
	bool	state;
	
	state = check_surrounding(*map, c);
	map->grid[c.x][c.y] = '1';
	if (state && 
		map->grid[c.x + 1][c.y] != ' ' && map->grid[c.x + 1][c.y] != '1')
		state = fill_space(map, (t_int_coord){c.x + 1, c.y});
	if (state &&
		map->grid[c.x][c.y + 1] != ' ' && map->grid[c.x][c.y + 1] != '1')
		state = fill_space(map, (t_int_coord){c.x, c.y + 1});
	if (state &&
		map->grid[c.x - 1][c.y] != ' ' && map->grid[c.x - 1][c.y] != '1')
		state = fill_space(map, (t_int_coord){c.x - 1, c.y});
	if (state &&
		map->grid[c.x][c.y - 1] != ' ' && map->grid[c.x][c.y - 1] != '1')
		state = fill_space(map, (t_int_coord){c.x, c.y - 1});
	return (state);
}

int check_map_valid(t_map map)
{
	t_int_coord	c;
	t_map		map_cpy;
	bool		map_ok;

	if (map.x < 3 || map.y < 3)
		return (MAP_TOO_SMALL);
	map_cpy.x = map.x;
	map_cpy.y = map.y;
	map_cpy.grid = new_map_grid(map.x, map.y);
	cpy_map_grid(map.grid, map_cpy.grid, map.x, map.y);
	c.y = -1;
	map_ok = true;
	while (map_ok && ++c.y < map.y)
	{
		c.x = -1;
		while (map_ok && ++c.x < map.x)
			if (map_cpy.grid[c.x][c.y] != ' ' && map_cpy.grid[c.x][c.y] != '1')
				map_ok = fill_space(&map_cpy, c);
	}
	free_map_grid(map_cpy);
	if (!map_ok)
		return (MAP_INCORRECT);
	return (0);
}

int	check_map_content(t_map map)
{
	int		x;
	int		y;
	bool	sprites;

	sprites = false;
	y = -1;
	while (++y < map.y)
	{
		x = -1;
		while (++x < map.x)
		{
			if (map.grid[x][y] != '0' && map.grid[x][y] != '1'
				&& map.grid[x][y] != '2' && map.grid[x][y] != ' '
				&& map.grid[x][y] != 'S' && map.grid[x][y] != 'N'
				&& map.grid[x][y] != 'E' && map.grid[x][y] != 'W')
				return (INCORRECT_VALUE);
			if (map.grid[x][y] == '2')
				sprites = true;
		}
	}
	if (sprites)
		return (1);
	return (0);
}

int	check_loaded_values(t_window win, int need_sprites)
{
	if (need_sprites == 1 && !win.game.textures.sprites)
		return (MISSING_VALUE);
	if (!win.load_res || !win.game.textures.c_loaded ||
		!win.game.textures.f_loaded || !win.game.textures.c_loaded ||
		!win.game.textures.n_tex || !win.game.textures.s_tex ||
		!win.game.textures.e_tex || !win.game.textures.w_tex)
		return (MISSING_VALUE);
	return (0);
}

void	check_res(void *mlx, int *width, int *height)
{
	int max_height;
	int max_width;

	mlx_get_screen_size(mlx, &max_width, &max_height);
	if (*height > max_height)
		*height = max_height;
	if (*width > max_width)
		*width = max_width;
}

void check_parsed_datas(t_window *win)
{
	int	error;

	error = check_map_valid(win->game.map);
	if (error < 0)
		error_exit(error, NULL, "Check map is valid", win);
	error = check_map_content(win->game.map);
	if (error < 0)
		error_exit(error, NULL, "Check map content", win);
	if (check_loaded_values(*win, error) < 0)
		error_exit(MISSING_VALUE, NULL, "Check loaded values", win);
	error = spawn_player(win->game.map, &win->game.player);
	if (error < 0)
		error_exit(error, NULL, "Get player Spawn", win);
	check_res(win->mlx, &win->width, &win->height);
	win->game.frames.f1 = new_image(win->mlx, win->width, win->height);
	if (!win->game.frames.f1)
		error_exit(MALLOC_ERROR, "Can\'t malloc frame f1", NULL, win);
	win->game.frames.f2 = new_image(win->mlx, win->width, win->height);
	if (!win->game.frames.f2)
		error_exit(MALLOC_ERROR, "Can\'t malloc frame f2", NULL, win);
	win->game.player.rays = malloc_rays(win->width);
	if (!win->game.player.rays)
		error_exit(MALLOC_ERROR, "Can\'t malloc rays", NULL, win);
}