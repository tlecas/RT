/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 17:06:57 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/13 17:00:30 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		main(int ac, char **av)
{
	t_env	*e = 0;

	if (ac != 2)
	{
		ft_error("usage: rt [filename]");
		return (0);
	}
	e = ft_init(av[1]);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, key_hook, e);
	ft_rt(e);
	mlx_loop(e->mlx);
	return (0);
}
