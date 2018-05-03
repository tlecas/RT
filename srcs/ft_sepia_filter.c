/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sepia_filter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 04:42:22 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 04:43:04 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int		ft_sepia_color(unsigned int r,
	unsigned int g, unsigned int b)
{
	unsigned int		r2;
	unsigned int		g2;
	unsigned int		b2;

	r2 = r * .39 + g * .77 + b * .19;
	g2 = r * .35 + g * .69 + b * .17;
	b2 = r * .27 + g * .53 + b * .13;
	uiclamp(&r2, 0, 255);
	uiclamp(&g2, 0, 255);
	uiclamp(&b2, 0, 255);
	return ((r2 << 16) + (g2 << 8) + b2);
}

void					ft_sepia_filter(t_env *e)
{
	int					i;
	unsigned int		tab[3];
	unsigned int		color;

	i = 0;
	while (i < e->win_area)
	{
		color = e->data[i];
		color <<= 8;
		tab[0] = (color >> 24);
		color <<= 8;
		tab[1] = (color >> 24);
		color <<= 8;
		tab[2] = (color >> 24);
		e->data[i] = ft_sepia_color(tab[0], tab[1], tab[2]);
		++i;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	ft_display_info(e->keys, e);
}
