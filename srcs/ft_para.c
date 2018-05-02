/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_para.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 21:47:43 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 20:39:10 by tlecas           ###   ########.fr       */
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
	thr->internorm = normalize(vectsub(vectsub(thr->interpos, thr->pos),
				vmult(thr->normal, m + thr->ar)));
	if (!(thr->e->para[i]->mat.refraction > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	*tmp = thr->e->para[i]->color;
}

float			ft_calc_para(t_para *para, t_ray *ray)
{
	float	tab[3];
	float	delta;
	float	tmp;
	t_vect	pos;

	if (!norm2(para->normal))
		para->normal = coord_v(0.0f, 1.0f, 0.0f);
	para->normal = normalize(para->normal);
	pos = vectsub(ray->pos, para->pos);
	tab[0] = dot(ray->dir, ray->dir) - powf(dot(ray->dir, para->normal), 2);
	tab[1] = 2.0f * (dot(pos, ray->dir) - dot(ray->dir, para->normal)
			* (dot(pos, para->normal) + 2.0f * para->k));
	tab[2] = dot(pos, pos) - dot(pos, para->normal)
			* (dot(pos, para->normal) + 4.0f * para->k);
	delta = tab[1] * tab[1] - 4.0f * tab[0] * tab[2];
	tmp = ft_eq_second(delta, tab[0], tab[1], tab[2]);
	if (tmp < 0.0001f)
		return (0);
	return (tmp);
}
