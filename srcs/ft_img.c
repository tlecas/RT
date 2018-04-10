/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:32:56 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:45:44 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void ft_put_pixel_to_img(t_thread *thr, int x, int y)
{
	unsigned char color1;
	unsigned char color2;
	unsigned char color3;
	unsigned int color;

	//soucis modification du meme tableau au sein de thread
	color = mlx_get_color_value(thr->e->mlx, thr->color);
	color1 = (color & 0xFF0000) >> 16;
	color2 = (color & 0x00FF00) >> 8;
	color3 = (color & 0x0000FF);

	//printf("%u\n", color);
	thr->e->data[y * thr->e->sizeline + x * (thr->e->bpp) / 8 ] = color3;
	thr->e->data[y * thr->e->sizeline + x * (thr->e->bpp) / 8 + 1] = color2;
	thr->e->data[y * thr->e->sizeline + x * (thr->e->bpp) / 8 + 2] = color1;
	//printf("%c\n", thr->e->data[y * thr->e->sizeline + x * (thr->e->bpp) / 8 ]);
}

void ft_print_obj(t_thread *thr, int x, int y)
{
	ft_put_pixel_to_img(thr, x, y);
	//printf("%c\n", thr->e->data[y * thr->e->sizeline + x * (thr->e->bpp) / 8 ]);
}
