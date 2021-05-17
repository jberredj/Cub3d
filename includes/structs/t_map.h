/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:05:07 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 12:07:01 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MAP_H
# define T_MAP_H
# include "t_img.h"
typedef struct s_map
{
	int		y;
	int		x;
	int		**grid;
	t_img	*img;
}t_map;


#endif