/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:54:17 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 11:32:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "mlx_utils.h"
#include "img.h"
#include "../libs/libft/includes/libft.h"

static void	write_image_to_bmp_file(t_img img, int fd)
{
	int	x;
	int	y;
	int	color;

	y = img.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < img.width)
		{
			color = get_color_from_mlx_img(img, x, y);
			write(fd, (char *) &color, 3);
			x++;
		}
		y--;
	}
}

static int	bmp_write_header(int fd, t_img img)
{
	unsigned char	headerfile[54];
	int				bmpsize;

	ft_bzero(headerfile, 54);
	bmpsize = 54 + (3 * img.width * img.height);
	headerfile[0] = (unsigned char)('B');
	headerfile[1] = (unsigned char)('M');
	headerfile[2] = (unsigned char)bmpsize;
	headerfile[3] = (unsigned char)(bmpsize >> 8);
	headerfile[4] = (unsigned char)(bmpsize >> 16);
	headerfile[5] = (unsigned char)(bmpsize >> 24);
	headerfile[10] = (unsigned char)(54);
	headerfile[14] = (unsigned char)(40);
	headerfile[18] = (unsigned char)img.width;
	headerfile[19] = (unsigned char)(img.width >> 8);
	headerfile[20] = (unsigned char)(img.width >> 16);
	headerfile[21] = (unsigned char)(img.width >> 24);
	headerfile[22] = (unsigned char)img.height;
	headerfile[23] = (unsigned char)(img.height >> 8);
	headerfile[24] = (unsigned char)(img.height >> 16);
	headerfile[25] = (unsigned char)(img.height >> 24);
	headerfile[26] = (unsigned char)(1);
	headerfile[28] = (unsigned char)(24);
	return (write(fd, headerfile, 54));
}

void	mlx_img_to_bmp(t_img img)
{
	int				file;

	file = open("./deepthought.bmp", O_WRONLY | O_CREAT,
			0666 | O_TRUNC | O_APPEND);
	bmp_write_header(file, img);
	write_image_to_bmp_file(img, file);
	close(file);
}
