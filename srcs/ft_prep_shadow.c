/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prep_shadow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 18:10:20 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 22:17:47 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_prepare_shadow_sphere(t_thread *thr, t_light *light)
{
	t_ray	shadow_eye;
	int			j;

	j = -1;
	shadow_eye.pos = thr->interpos;
	shadow_eye.dir = light->vect;
	while (++j < thr->e->objnb->totobj)
	{
		if (j < thr->e->objnb->plane && ft_shadow_plane(thr, j, &shadow_eye))
			return (1);
		if (thr->number != j && j < thr->e->objnb->sphere && ft_shadow_sphere(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cone && ft_shadow_cone(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cylinder && ft_shadow_cylinder(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->para && ft_shadow_para(thr, j, &shadow_eye))
			return (1);
	}
	return (0);
}

int		ft_prepare_shadow_plane(t_thread *thr, t_light *light)
{
	t_ray	shadow_eye;
	int			j;

	j = -1;
	shadow_eye.pos = thr->interpos;
	shadow_eye.dir = light->vect;
	while (++j < thr->e->objnb->totobj)
	{
		if (thr->number != j && j < thr->e->objnb->plane && ft_shadow_plane(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->sphere && ft_shadow_sphere(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cone && ft_shadow_cone(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cylinder && ft_shadow_cylinder(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->para && ft_shadow_para(thr, j, &shadow_eye))
			return (1);
	}
	return (0);
}

int		ft_prepare_shadow_cone(t_thread *thr, t_light *light)
{
	t_ray	shadow_eye;
	int			j;

	j = -1;
	shadow_eye.pos = thr->interpos;
	shadow_eye.dir = light->vect;
	while (++j <thr->e->objnb->totobj)
	{
		if (j < thr->e->objnb->plane && ft_shadow_plane(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->sphere && ft_shadow_sphere(thr, j, &shadow_eye))
			return (1);
		if (thr->number != j && j < thr->e->objnb->cone && ft_shadow_cone(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cylinder && ft_shadow_cylinder(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->para && ft_shadow_para(thr, j, &shadow_eye))
			return (1);
	}
	return (0);
}

int		ft_prepare_shadow_cylinder(t_thread *thr, t_light *light)
{
	t_ray	shadow_eye;
	int			j;

	j = -1;
	shadow_eye.pos = thr->interpos;
	shadow_eye.dir = light->vect;
	while (++j < thr->e->objnb->totobj)
	{
		if (j < thr->e->objnb->plane && ft_shadow_plane(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->sphere && ft_shadow_sphere(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cone && ft_shadow_cone(thr, j, &shadow_eye))
			return (1);
		if (thr->number != j && j < thr->e->objnb->cylinder && ft_shadow_cylinder(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->para && ft_shadow_para(thr, j, &shadow_eye))
			return (1);
	}
	return (0);
}

int		ft_prepare_shadow_para(t_thread *thr, t_light *light)
{
	t_ray	shadow_eye;
	int			j;

	j = -1;
	shadow_eye.pos = thr->interpos;
	shadow_eye.dir = light->vect;
	while (++j < thr->e->objnb->totobj)
	{
		if (j < thr->e->objnb->plane && ft_shadow_plane(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->sphere && ft_shadow_sphere(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cone && ft_shadow_cone(thr, j, &shadow_eye))
			return (1);
		if (j < thr->e->objnb->cylinder && ft_shadow_cylinder(thr, j, &shadow_eye))
			return (1);
		if (thr->number != j && j < thr->e->objnb->para && ft_shadow_para(thr, j, &shadow_eye))
			return (1);
	}
	return (0);
}

int		ft_is_shadow(t_thread *thr, t_light *light)
{
	if (!(ft_strcmp(thr->name, "sphere")))
			return (ft_prepare_shadow_sphere(thr, light));
	else if (!(ft_strcmp(thr->name, "plane")))
			return (ft_prepare_shadow_plane(thr, light));
	else if (!(ft_strcmp(thr->name, "cylinder")))
			return (ft_prepare_shadow_cylinder(thr, light));
	else if (!(ft_strcmp(thr->name, "cone")))
			return (ft_prepare_shadow_cone(thr, light));
	else if (!(ft_strcmp(thr->name, "para")))
			return (ft_prepare_shadow_cone(thr, light));
	return (0);
}
