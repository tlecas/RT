/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:30:37 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/27 06:20:58 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_save_inter_cylinder(t_thread *thr, t_cylinder *cylinder, t_ray *ray)
{
	t_vect	norm;
	float	dotc;

	dotc = 0.0f;
	norm = vrotate(coord_v(0.0f, 1.0f, 0.0f), cylinder->rotate);
	thr->interpos = vectadd(ray->pos, vmult(ray->dir, thr->value));
	thr->internorm = vectsub(thr->interpos, cylinder->pos);
	dotc = dot(norm, thr->internorm);
	thr->internorm = vectsub(thr->internorm, vmult(norm, dotc));
	thr->internorm = normalize(thr->internorm);
	if (!(cylinder->mat.refraction) && (thr->e->keys & ROUGH))
	thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
}

void			ft_post_cylinder(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->cylinder[i]->radius;
	thr->pos = thr->e->cylinder[i]->pos;
	thr->rotate = thr->e->cylinder[i]->rotate;
	ft_save_inter_cylinder(thr, thr->e->cylinder[i], &thr->ray);
	*tmp = thr->e->cylinder[i]->color;
}

float			ft_calc_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vect	pos;
	t_vect	tmp;

	tmp = vrotate(coord_v(0.0f, 1.0f, 0.0f), cylinder->rotate);
	pos = vectsub(ray->pos, cylinder->pos);
	a = dot(ray->dir, ray->dir) - dot(ray->dir, tmp) * dot(ray->dir, tmp);
	b = 2.0f * (dot(pos, ray->dir) - dot(ray->dir, tmp) * dot(pos, tmp));
	c = dot(pos, pos) - dot(pos, tmp) * dot(pos, tmp) - (cylinder->radius * cylinder->radius);
	delta = b * b - 4.0f * a * c;
	return (ft_eq_second(delta, a, b, c));
}
