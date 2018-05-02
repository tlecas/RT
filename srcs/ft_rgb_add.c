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

static void		ft_sepia_color(unsigned int *color, unsigned int r,
					unsigned int g, unsigned int b)
{
	unsigned int r2;
	unsigned int g2;
	unsigned int b2;

	r2 = r * .39 + g * .77 + b * .19;
	g2 = r * .35 + g * .69 + b * .17;
	b2 = r * .27 + g * .53 + b * .13;
	uiclamp(&r2, 0, 255);
	uiclamp(&g2, 0, 255);
	uiclamp(&b2, 0, 255);
	*color = (r2 << 16) + (g2 << 8) + b2;
}

static void		ft_rgb_add_sepia(unsigned int *d, unsigned int *color,
			t_thread *thr)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int filtbw;

	r = (*color >> 24) + (*d >> 24);
	uiclamp(&r, 0, 255);
	*color <<= 8;
	*d <<= 8;
	g = (*color >> 24) + (*d >> 24);
	uiclamp(&g, 0, 255);
	*color <<= 8;
	*d <<= 8;
	b = (*color >> 24) + (*d >> 24);
	uiclamp(&b, 0, 255);
	if (thr->keys & BLACK)
	{
		filtbw = (r + g + b) / 3;
		*color = (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		ft_sepia_color(color, r, g, b);
}

static void		ft_rgb_add_cartoon(unsigned int *d, unsigned int *color,
			t_thread *thr)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int filtbw;

	r = ((*color >> 28) + (*d >> 28)) << 4;
	uiclamp(&r, 0, 255);
	*color <<= 8;
	*d <<= 8;
	g = ((*color >> 28) + (*d >> 28)) << 4;
	uiclamp(&g, 0, 255);
	*color <<= 8;
	*d <<= 8;
	b = ((*color >> 28) + (*d >> 28)) << 4;
	uiclamp(&b, 0, 255);
	if (thr->keys & BLACK)
	{
		filtbw = (r + g + b) / 3;
		*color = (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		*color = (r << 16) + (g << 8) + b;
}

static void		rgb_define_rg(unsigned int *r, unsigned int *g,
						unsigned int *d, unsigned int *color)
{
	*r = (*color >> 24) + (*d >> 24);
	uiclamp(r, 0, 255);
	*color <<= 8;
	*d <<= 8;
	*g = (*color >> 24) + (*d >> 24);
	uiclamp(g, 0, 255);
	*color <<= 8;
	*d <<= 8;
}

void			rgb_add(unsigned int *color, unsigned int d, t_thread *thr)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int filtbw;

	*color <<= 8;
	d <<= 8;
	if (thr->keys & CARTOON)
		ft_rgb_add_cartoon(&d, color, thr);
	else if (thr->keys & SEPIA)
		ft_rgb_add_sepia(&d, color, thr);
	else
	{
		rgb_define_rg(&r, &g, &d, color);
		b = (*color >> 24) + (d >> 24);
		uiclamp(&b, 0, 255);
	}
	if (thr->keys & BLACK)
	{
		filtbw = (r + g + b) / 3;
		*color = (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		*color = (r << 16) + (g << 8) + b;
}
