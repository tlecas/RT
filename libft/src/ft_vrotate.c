/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vrotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:53:29 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/27 07:02:47 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vect	rotate_x(t_vect v, float angle)
{
	float	y_tmp;
	float	z_tmp;

	angle = angle * M_PI / 180.0f;
	y_tmp = v.y;
	z_tmp = v.z;
	v.y = y_tmp * cosf(angle) - z_tmp * sinf(angle);
	v.z = y_tmp * sinf(angle) + z_tmp * cosf(angle);
	return (v);
}

t_vect	rotate_y(t_vect v, float angle)
{
	double	x_tmp;
	double	z_tmp;

	angle = angle * M_PI / 180.0f;
	x_tmp = v.x;
	z_tmp = v.z;
	v.z = z_tmp * cosf(angle) - x_tmp * sinf(angle);
	v.x = z_tmp * sinf(angle) + x_tmp * cosf(angle);
	return (v);
}

t_vect	rotate_z(t_vect v, float angle)
{
	double	x_tmp;
	double	y_tmp;

	angle = angle * M_PI / 180.0f;
	x_tmp = v.x;
	y_tmp = v.y;
	v.x = x_tmp * cosf(angle) - y_tmp * sinf(angle);
	v.y = x_tmp * sinf(angle) + y_tmp * cosf(angle);
	return (v);
}

t_vect	vrotate(t_vect v, t_vect angle)
{
	v = rotate_x(v, (angle.x));
	v = rotate_y(v, (angle.y));
	v = rotate_z(v, (angle.z));
	return (v);
}
