/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hud.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpagot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 23:34:00 by rpagot            #+#    #+#             */
/*   Updated: 2018/04/29 23:34:04 by rpagot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_display_info(unsigned int keys, t_env *e)
{
	if (keys & AA)
		mlx_string_put(e->mlx, e->win, 10, 10, 0x0000FF00, "ANTIALIASING X2");
	if (keys & ROUGH)
		mlx_string_put(e->mlx, e->win, 10, 30, 0x0000FF00, "ROUGH SURFACE");
	if (keys & BLACK)
		mlx_string_put(e->mlx, e->win, 10, 50, 0x0000FF00, "BLACK FILTER");
	if (keys & FRACTAL)
		mlx_string_put(e->mlx, e->win, 10, 70, 0x0000FF00, "FRACTAL FILTER");
	if (keys & CARTOON)
		mlx_string_put(e->mlx, e->win, 10, 90, 0x0000FF00, "CARTOON FILTER");
	if (keys & SEPIA)
		mlx_string_put(e->mlx, e->win, 10, 110, 0x0000FF00, "SEPIA FILTER");
	if (keys & BLUR)
		mlx_string_put(e->mlx, e->win, 10, 130, 0x0000FF00, "BLUR");
}
