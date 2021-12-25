/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_ray.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberredj <jberredj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:56:39 by jberredj          #+#    #+#             */
/*   Updated: 2021/05/17 12:02:23 by jberredj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_RAY_H
# define T_RAY_H
# include <stdbool.h>
typedef struct	s_ray
{
	double	rayAngle;
	int		raynbr;
	double	o_x;
	double	o_y;
	bool	rayDown;
	bool	rayRight;
	double	wallHitX;
	double	wallHitY;
	bool	wasHitVertical;
	double	stripHeight;
	double	distance;
}				t_ray;

#endif