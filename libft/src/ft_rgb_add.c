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

void	rgb_add(unsigned int *color, unsigned int add)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int inv;

	inv = (*color / 0x1000000);
	*color = *color % 0x1000000;
	add = add % 0x1000000;
	//printf("color = %d add = %d\n", (*color / 0x10000), (add / 0x10000));
	r = (*color / 0x10000) + (add / 0x10000);
	//printf("r = %d\n", r);
	uiclamp(&r, 0, 255);
	*color = *color % 0x10000;
	add = add % 0x10000;
	//printf("color = %d add = %d\n", (*color / 0x100), (add / 0x100));
	g = (*color / 0x100) + (add / 0x100);
	//printf("g = %d\n", g);
	uiclamp(&g, 0, 255);
	*color = *color % 0x100;
	add = add % 0x100;
	//printf("color = %d add = %d\n", *color, add);
	b = *color + add;
	//printf("b = %d\n", b);
	uiclamp(&b, 0, 255);
	*color =(inv * 0x1000000) + (r * 0x10000) + (g * 0x100) + b;
}
