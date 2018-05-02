/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:30:37 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 20:38:42 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_post_cylinder(t_thread *thr, unsigned int *tmp)
{
	int		i;
	float	m;

	i = thr->number;
	thr->ar = thr->e->cylinder[i]->radius;
	thr->pos = thr->e->cylinder[i]->pos;
	thr->axis = thr->e->cylinder[i]->axis;
	thr->interpos = vectadd(thr->ray.pos, vmult(thr->ray.dir, thr->value));
	m = dot(thr->ray.dir, thr->axis) * thr->value
		+ dot(thr->ray.pos, thr->axis);
	thr->internorm = normalize(vectsub(vectsub(thr->interpos, thr->pos),
				vmult(thr->axis, m)));
	if (!(thr->e->cylinder[i]->mat.refraction > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	*tmp = thr->e->cylinder[i]->color;
}

float			ft_calc_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float	tab[3];
	float	delta;
	t_vect	pos;
	float	tmp;

	if (!norm2(cylinder->axis))
		cylinder->axis = coord_v(0.0f, 1.0f, 0.0f);
	cylinder->axis = normalize(cylinder->axis);
	pos = vectsub(ray->pos, cylinder->pos);
	tab[0] = dot(ray->dir, ray->dir) - dot(ray->dir, cylinder->axis)
			* dot(ray->dir, cylinder->axis);
	tab[1] = 2.0f * (dot(pos, ray->dir) - dot(ray->dir, cylinder->axis)
			* dot(pos, cylinder->axis));
	tab[2] = dot(pos, pos) - dot(pos, cylinder->axis) * dot(pos, cylinder->axis)
			- (cylinder->radius * cylinder->radius);
	delta = tab[1] * tab[1] - 4.0f * tab[0] * tab[2];
	tmp = ft_eq_second(delta, tab[0], tab[1], tab[2]);
	if (tmp < 0.0001f)
		return (0);
	return (tmp);
}
