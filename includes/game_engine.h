/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_engine.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:18:24 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 14:47:06 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_ENGINE_H
# define GAME_ENGINE_H
# include <stdbool.h>
# include "structs/t_window.h"
# include "structs/t_game.h"

int		game_loop(t_window *win);
void	create_win(t_window *win);
void	free_exit(t_window *win);
t_game	init_game_engine(void);
#endif