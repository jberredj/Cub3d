/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 10:41:51 by jberredj          #+#    #+#             */
/*   Updated: 2020/12/14 17:56:08 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*uchar_dest;
	unsigned char	*uchar_src;

	if (dest == NULL && src == NULL)
		return (NULL);
	uchar_dest = (unsigned char*)dest;
	uchar_src = (unsigned char*)src;
	while (n-- > 0)
		*uchar_dest++ = *uchar_src++;
	return (dest);
}
