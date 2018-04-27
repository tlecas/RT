/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:10:19 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/27 06:06:07 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_save_inter_cone(t_thread *thr, t_cone *cone, t_ray *ray)
{
	t_vect	norm;
	double	dotc;

	dotc = 0.0;
	norm = vrotate(coord_v(0.0, 1.0, 0.0), cone->rotate);
	thr->interpos = vectadd(ray->pos, vmult(ray->dir, thr->value));
	thr->internorm = vectsub(thr->interpos, cone->pos);
	dotc = dot(norm, thr->internorm);
	thr->internorm = vectsub(thr->internorm, vmult(norm, dotc));
	thr->internorm = normalize(thr->internorm);
	if (!(cone->mat.refraction) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f); // surface rugueuse
}

void		ft_post_cone(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->cone[i]->angle;
	thr->pos = thr->e->cone[i]->pos;
	thr->rotate = thr->e->cone[i]->rotate;
	ft_save_inter_cone(thr, thr->e->cone[i], &thr->ray);
	*tmp = thr->e->cone[i]->color;
}

float			ft_calc_cone(t_cone *cone, t_ray *ray)
{
	t_vect	normal;
	float	a;
	float	b;
	float	c;
	t_vect	pos;
	float	delta;
	float	tmp;

	normal = vrotate(coord_v(0.0f, 1.0f, 0.0f), cone->rotate);
	pos = vectsub(ray->pos, cone->pos);
	tmp = dot(ray->dir, normal);
	a = POW2(tmp) - POW2(cos(cone->angle * (M_PI / 180.0f)));
	b = 2.0f * (tmp * dot(pos, normal) - dot(ray->dir, pos) * POW2(cos(cone->angle * (M_PI / 180.0f))));
	c = POW2(dot(pos, normal)) - dot(pos, pos) * POW2(cos(cone->angle * (M_PI / 180.0f)));
	delta = b * b - 4.0f * a * c;
	return (ft_eq_second(delta, a, b, c));
}
