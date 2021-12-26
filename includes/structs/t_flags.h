/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_flags.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:55:40 by jberredj          #+#    #+#             */
/*   Updated: 2021/12/26 01:43:07 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_FLAGS_H
# define T_FLAGS_H
# include <stdbool.h>

typedef struct s_flags
{
	bool	show_map;
	bool	mouse_control;
	bool	pause;
}				t_flags;
#endif