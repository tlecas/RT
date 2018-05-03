/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cartoon_filter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 04:43:19 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 04:43:20 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_cartoon_filter(t_env *e)
{
	int				i;
	unsigned int	tab[3];
	unsigned int	color;

	i = 0;
	while (i < e->win_area)
	{
		color = e->data[i];
		color <<= 8;
		tab[0] = (color >> 28) << 4;
		color <<= 8;
		tab[1] = (color >> 28) << 4;
		color <<= 8;
		tab[2] = (color >> 28) << 4;
		e->data[i] = (tab[0] << 16) + (tab[1] << 8) + tab[2];
		++i;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	ft_display_info(e->keys, e);
}
