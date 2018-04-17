/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normalize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 16:40:09 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:05:45 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	norm2(t_vect v)
{
	float norm2;

	norm2 = (v.x * v.x + v.y * v.y + v.z * v.z);
	return (norm2);
}

float	norm(t_vect v)
{
	float norm;

	norm = sqrt(norm2(v));
	return (norm);
}

t_vect	normalize(t_vect v)
{
	float normv;

	normv = norm(v);
	v.x /= normv;
	v.y /= normv;
	v.z /= normv;
	return (v);
}
