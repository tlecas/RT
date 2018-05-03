/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 03:49:21 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 03:54:47 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int		ft_calc_more(t_thread *thr, int i, int x, float *obj)
{
	while (thr->e->objnb->cylinder != 0 && (x) < thr->e->objnb->cylinder)
	{
		obj[i] = ft_calc_cylinder(thr->e->cylinder[x], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	while (thr->e->objnb->cone != 0 && (x) < thr->e->objnb->cone)
	{
		obj[i] = ft_calc_cone(thr->e->cone[x], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	while (thr->e->objnb->para != 0 && (x) < thr->e->objnb->para)
	{
		obj[i] = ft_calc_para(thr->e->para[x], &thr->ray);
		i++;
		++x;
	}
	i = ft_isview(obj, i - 1);
	return (ft_load_post(thr, i, obj[i]));
}

unsigned int			ft_calc_obj(t_thread *thr, int recursivity)
{
	float				obj[thr->e->objnb->totobj];
	int					i;
	int					x;

	x = 0;
	i = 0;
	thr->recursivity = recursivity;
	while (thr->e->objnb->sphere != 0 && i < thr->e->objnb->sphere)
	{
		obj[i] = ft_calc_sphere(thr->e->sphere[i], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	while (thr->e->objnb->plane != 0 && (x) < thr->e->objnb->plane)
	{
		obj[i] = ft_calc_plan(thr->e->plane[x], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	return (ft_calc_more(thr, i, x, obj));
}
