/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idllst_is_head.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:29:35 by jberredj          #+#    #+#             */
/*   Updated: 2021/11/17 08:53:47 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_idllst.h"
#include <stdbool.h>

bool	ft_idllst_is_head(t_idllist *node)
{
	if (!ft_idllst_is_init(node))
		return (false);
	return ((bool)(node->prev == node));
}
