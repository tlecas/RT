/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 17:06:57 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 23:54:55 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			close_window(t_env *e)
{
	mlx_destroy_window(e->mlx, e->win);
	mlx_destroy_image(e->mlx, e->img);
	free(e);
	exit(EXIT_FAILURE);
}

int					main(int ac, char **av)
{
	t_env	*e;

	e = 0;
	if (ac != 2)
	{
		ft_error("usage: rt [filename]", 0, 0);
		return (0);
	}
	e = ft_init(av[1]);
	if (e->antialias)
		e->keys ^= AA;
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, key_hook, e);
	mlx_hook(e->win, 17, (1L << 17), &close_window, e);
	ft_rt(e);
	mlx_loop(e->mlx);
	free(e);
	return (0);
}
