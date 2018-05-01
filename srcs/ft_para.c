/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_para.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 21:47:43 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 22:34:40 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_post_para(t_thread *thr, unsigned int *tmp)
{
	int		i;
	float	m;

	i = thr->number;
	thr->ar = thr->e->para[i]->k;
	thr->pos = thr->e->para[i]->pos;
	thr->normal = thr->e->para[i]->normal;
	thr->interpos = vectadd(thr->ray.pos, vmult(thr->ray.dir, thr->value));
	m = dot(vectsub(thr->interpos, thr->pos), thr->normal);
	thr->internorm = normalize(vectsub(vectsub(thr->interpos, thr->pos), vmult(thr->normal, m + thr->ar)));
	if (!(thr->e->para[i]->mat.refraction > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	*tmp = thr->e->para[i]->color;
}

float		ft_calc_para(t_para *para, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	tmp;
	t_vect	pos;

	if (!norm2(para->normal))
		para->normal = coord_v(0.0f, 1.0f, 0.0f);
	para->normal = normalize(para->normal);
	pos = vectsub(ray->pos, para->pos);
	a = dot(ray->dir, ray->dir) - powf(dot(ray->dir, para->normal), 2);
	b = 2.0f * (dot(pos, ray->dir) - dot(ray->dir, para->normal) * (dot(pos, para->normal) + 2.0f * para->k));
	c = dot(pos, pos) - dot(pos, para->normal) * (dot(pos, para->normal) + 4.0f * para->k);
	delta = b * b - 4.0f * a * c;
	tmp = ft_eq_second(delta, a, b, c);
	if (tmp < 0.0001f)
		return (0);
	return (tmp);
}
