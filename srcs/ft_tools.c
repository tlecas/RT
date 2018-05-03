/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 15:16:19 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 04:25:01 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static unsigned int		ambient_light(t_thread *thr, unsigned int color)
{
	unsigned int		ambient;
	unsigned int		tab[3];
	unsigned int		tmp;
	float				doto;

	doto = fclamp((dot(vmult(thr->ray.dir, -1),
					thr->internorm) + 0.0 * 0.15), 0, 1);
	tmp = color;
	ambient = 0x00FFFFFF;
	tmp <<= 8;
	ambient <<= 8;
	tab[0] = uimin((ambient >> 24), (tmp >> 24)) * thr->mat.ambient * doto;
	uiclamp(&tab[0], 0, 255);
	tmp <<= 8;
	ambient <<= 8;
	tab[1] = uimin((ambient >> 24), (tmp >> 24)) * thr->mat.ambient * doto;
	uiclamp(&tab[1], 0, 255);
	uimin(tab[1], (tmp >> 24));
	tmp <<= 8;
	ambient <<= 8;
	tab[2] = uimin((ambient >> 24), (tmp >> 24)) * thr->mat.ambient * doto;
	uiclamp(&tab[2], 0, 255);
	ambient = (tab[0] << 16) + (tab[1] << 8) + tab[2];
	return (ambient);
}

static	int				ft_which_obj_helper(t_thread *thr, int *i, char **name)
{
	int					hit;

	hit = 0;
	if (*i < thr->e->objnb->sphere)
	{
		*name = ft_strdup("sphere");
		thr->mat = thr->e->sphere[*i]->mat;
		hit = 1;
	}
	else if (*i < thr->e->objnb->sphere + thr->e->objnb->plane)
	{
		*name = ft_strdup("plane");
		*i -= thr->e->objnb->sphere;
		thr->mat = thr->e->plane[*i]->mat;
		hit = 1;
	}
	else if (*i < thr->e->objnb->sphere + thr->e->objnb->plane
			+ thr->e->objnb->cylinder)
	{
		*name = ft_strdup("cylinder");
		*i -= thr->e->objnb->sphere + thr->e->objnb->plane;
		thr->mat = thr->e->cylinder[*i]->mat;
		hit = 1;
	}
	return (hit);
}

static	char			*ft_which_obj(t_thread *thr, int *i)
{
	char				*name;

	name = NULL;
	if (!(ft_which_obj_helper(thr, i, &name)))
	{
		if (*i < thr->e->objnb->sphere + thr->e->objnb->plane
				+ thr->e->objnb->cylinder + thr->e->objnb->cone)
		{
			name = ft_strdup("cone");
			*i -= thr->e->objnb->sphere + thr->e->objnb->plane +
				thr->e->objnb->cylinder;
			thr->mat = thr->e->cone[*i]->mat;
		}
		else if (*i < thr->e->objnb->sphere + thr->e->objnb->plane
				+ thr->e->objnb->cylinder + thr->e->objnb->cone +
					thr->e->objnb->para)
		{
			name = ft_strdup("para");
			*i -= thr->e->objnb->sphere + thr->e->objnb->plane
				+ thr->e->objnb->cylinder + thr->e->objnb->cone;
			thr->mat = thr->e->para[*i]->mat;
		}
	}
	return (name);
}

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

unsigned int			ft_load_post(t_thread *thr, int i, float obj)
{
	char				*name;
	int					j;
	unsigned int		color[thr->e->objnb->light + 1];
	unsigned int		ambient;
	unsigned int		tmp;

	j = -1;
	name = 0;
	tmp = 0x00000000;
	thr->value = obj;
	if (obj > 0.0f)
	{
		name = ft_which_obj(thr, &i);
		thr->name = name;
		thr->number = i;
		thr->value = obj;
		post_obj(thr, &tmp);
		ambient = ambient_light(thr, tmp);
		while (++j < thr->e->objnb->light)
		{
			thr->light = *thr->e->light[j];
			color[j] = ft_light(thr, &thr->light, tmp);
		}
		j = -1;
		tmp = 0x00000000;
		while (++j < (thr->e->objnb->light))
			rgb_add(&tmp, color[j], thr);
		rgb_add(&tmp, ambient, thr);
		if ((thr->mat.refraction > 0.0f && thr->recursivity > 0)
				|| (thr->mat.reflection > 0.0f && thr->recursivity > 0))
			reflaction(thr, &tmp);
	}
	ft_strdel(&name);
	return (tmp);
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
