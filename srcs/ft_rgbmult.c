/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbmult.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 00:24:06 by rpagot            #+#    #+#             */
/*   Updated: 2018/05/03 00:24:09 by rpagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				rgb_mult(unsigned int *color, float f, t_thread *thr)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if ((thr->keys & FRACTAL))
		*color *= f;
	else
	{
		*color <<= 8;
		r = (*color >> 24) * f;
		*color <<= 8;
		g = (*color >> 24) * f;
		*color <<= 8;
		b = (*color >> 24) * f;
		*color = (r << 16) + (g << 8) + b;
	}
}
