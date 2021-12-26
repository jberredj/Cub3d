/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:55:40 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:50:29 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBOARD_H
# define KEYBOARD_H
# include "structs/t_window.h"

int	key_pressed(int keycode, t_window *win);
int	key_released(int keycode, t_window *win);
#endif