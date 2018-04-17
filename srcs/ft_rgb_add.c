/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:05:14 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:05:04 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rt.h"

void	rgb_add(unsigned int *color, unsigned int d, t_thread *thr)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int inv;
	unsigned int filtbw;


	inv = (*color >> 24) + (d >> 24);
	*color <<= 8;
	d <<= 8;
	r = (*color >> 24) + (d >> 24);
	uiclamp(&r, 0, 255);
	*color <<= 8;
	d <<= 8;
	g = (*color >> 24) + (d >> 24);
	uiclamp(&g, 0, 255);
	*color <<= 8;
	d <<= 8;
	b = (*color >> 24) + (d >> 24);
	uiclamp(&b, 0, 255);
	if (thr->keys & 0x00000001)
	{
		filtbw = (r + g + b) / 3;
		*color = (inv << 24) + (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		*color = (inv << 24) + (r << 16) + (g << 8) + b;
}
