/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:16:19 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 06:16:06 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					post_obj(t_thread *thr, unsigned int *tmp)
{
	if (!(ft_strcmp(thr->name, "sphere")))
		ft_post_sphere(thr, tmp);
	if (!(ft_strcmp(thr->name, "plane")))
		ft_post_plane(thr, tmp);
	if (!(ft_strcmp(thr->name, "cylinder")))
		ft_post_cylinder(thr, tmp);
	if (!(ft_strcmp(thr->name, "cone")))
		ft_post_cone(thr, tmp);
	if (!(ft_strcmp(thr->name, "para")))
		ft_post_para(thr, tmp);
}

void					reflaction(t_thread *thr, unsigned int *tmp)
{
	float				kr;

	kr = fresnel(thr);
	if (kr < 1)
		*tmp = refracted(thr, *tmp, kr);
	*tmp = reflected(thr, *tmp, kr);
}

void					ftn(t_thread *thr, int *i, float obj)
{
	thr->lname = ft_which_obj(thr, i);
	thr->name = thr->lname;
	thr->number = *i;
	thr->value = obj;
	post_obj(thr, &(thr->ltmp));
	thr->lambient = ambient_light(thr, thr->ltmp);
}

unsigned int			ft_load_post(t_thread *thr, int i, float obj)
{
	unsigned int		color[thr->e->objnb->light + 1];

	thr->lj = -1;
	thr->lname = 0;
	thr->ltmp = 0x00000000;
	thr->value = obj;
	if (obj > 0.0f)
	{
		ftn(thr, &i, obj);
		while (++(thr->lj) < thr->e->objnb->light)
		{
			thr->light = *thr->e->light[thr->lj];
			color[thr->lj] = ft_light(thr, &thr->light, thr->ltmp);
		}
		thr->lj = -1;
		thr->ltmp = 0x00000000;
		while (++(thr->lj) < thr->e->objnb->light)
			rgb_add(&(thr->ltmp), color[(thr->lj)]);
		rgb_add(&(thr->ltmp), thr->lambient);
		if ((thr->mat.refraction > 0.0f && thr->recursivity > 0)
				|| (thr->mat.reflection > 0.0f && thr->recursivity > 0))
			reflaction(thr, &(thr->ltmp));
	}
	ft_strdel(&(thr->lname));
	return (thr->ltmp);
}

int						ft_isview(float *obj, int i)
{
	int					x;
	int					j;

	j = 0;
	x = -1;
	if (i > 0)
		while (++x <= i)
			if (obj[j] == 0.0f || (obj[x] < obj[j] && obj[x] > 0.0f))
				j = x;
	return (j);
}
