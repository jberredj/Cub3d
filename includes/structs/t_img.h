/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_img.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:06:06 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:44:40 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_IMG_H
# define T_IMG_H
# include <stdbool.h>

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_textures
{
	t_img	*n_tex;
	t_img	*e_tex;
	t_img	*s_tex;
	t_img	*w_tex;
	t_img	*sprites;
	bool	f_loaded;
	int		f_color;
	bool	c_loaded;
	int		c_color;
}				t_textures;

typedef struct s_square
{
	int	x;
	int	y;
	int	size;
	int	color;
}				t_square;

typedef struct s_circle
{
	int		x;
	int		y;
	double	radius;
	int		color;
}				t_circle;

typedef struct s_frames
{
	t_img	*f1;
	t_img	*f2;
}				t_frames;
#endif