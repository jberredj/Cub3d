/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 14:55:51 by jberredj          #+#    #+#             */
/*   Updated: 2020/12/24 15:11:51 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*uchar_s;

	uchar_s = (unsigned char*)s;
	while (n-- > 0)
		*uchar_s++ = (char)c;
	return (s);
}
