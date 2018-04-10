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
#include "libft.h"

/*void	rgb_add(unsigned int *color, unsigned int d)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int inv;

	inv = (*color >> 24);
	*color <<= 8;
	r = (*color >> 24) + d;
	uiclamp(&r, 0, 255);
	*color <<= 8;
	g = (*color >> 24) + d;
	uiclamp(&g, 0, 255);
	*color <<= 8;
	b = (*color >> 24) + d;
	uiclamp(&b, 0, 255);
	*color = (inv << 24) + (r << 16) + (g << 8) + b;
} BLACK WHITE FILTER*/

void	rgb_add(unsigned int *color, unsigned int d)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int inv;

	inv = (*color >> 24);
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
	*color = (inv << 24) + (r << 16) + (g << 8) + b;
}
