/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:47:39 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:57:02 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "structs/t_window.h"

int	mouse_in(t_window *win)
{
	win->game.mouse.mouse_in = true;
	return (0);
}

int	mouse_out(t_window *win)
{
	win->game.mouse.mouse_in = false;
	return (0);
}
