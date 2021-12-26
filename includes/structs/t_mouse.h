/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_mouse.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:47:00 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:45:19 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MOUSE_H
# define T_MOUSE_H
# include <stdbool.h>

typedef struct s_mouse
{
	int		x_vel;
	int		y_vel;
	int		last_x;
	int		last_y;
	bool	mouse_in;
}				t_mouse;
#endif