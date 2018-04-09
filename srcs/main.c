/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachena <gmachena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 17:06:57 by gmachena          #+#    #+#             */
/*   Updated: 2018/03/28 15:31:00 by gmachena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int g_x = 0;
int g_y = 0;


int		main(int ac, char **av)
{
	t_env	*e = 0;

	if (ac != 2)
	{
		ft_error("usage: rtv1 [filename]");
		return (0);
	}
	e = ft_init(av[1]);
//	mlx_mouse_hook(e->win, ft_mouse, e);
//	mlx_hook(e->win, DESTROYNOTIFY, STRUCTURENOTIFYMASK, close_hook, e);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, key_hook, e);
	ft_rt(e);
	mlx_loop(e->mlx);
	return (0);
}
