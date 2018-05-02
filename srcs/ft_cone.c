/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:10:19 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 16:14:27 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_post_cone(t_thread *thr, unsigned int *tmp)
{
	int		i;
	double	m;
	double	k;

	i = thr->number;
	thr->ar = thr->e->cone[i]->angle;
	thr->pos = thr->e->cone[i]->pos;
	thr->axis = thr->e->cone[i]->axis;
	thr->interpos = vectadd(thr->ray.pos, vmult(thr->ray.dir, thr->value));
	m = ddot(thr->ray.dir, thr->axis) * thr->value
		+ ddot(thr->ray.pos, thr->axis);
	k = tan(thr->ar * (M_PI / 180));
	thr->internorm = normalize(vectsub(vectsub(thr->interpos, thr->pos),
				vmult(vmult(thr->axis, (1 + k * k)), m)));
	if (!(thr->e->cone[i]->mat.refraction > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	*tmp = thr->e->cone[i]->color;
}

double		ft_calc_cone(t_cone *cone, t_ray *ray)
{
	double	tab[3];
	t_vect	pos;
	double	delta;
	double	tmp;
	double	k;

	if (!norm2(cone->axis))
		cone->axis = coord_v(0.0f, 1.0f, 0.0f);
	cone->axis = normalize(cone->axis);
	pos = vectsub(ray->pos, cone->pos);
	k = tan(cone->angle * (M_PI / 180));
	tab[0] = dot(ray->dir, ray->dir) - (1 + k * k)
		* pow(dot(ray->dir, cone->axis), 2);
	tab[1] = 2.0f * (dot(pos, ray->dir) - (1 + k * k)
			* dot(ray->dir, cone->axis) * dot(pos, cone->axis));
	tab[2] = dot(pos, pos) - (1 + k * k) * pow(dot(pos, cone->axis), 2);
	delta = tab[1] * tab[1] - 4.0 * tab[0] * tab[2];
	tmp = (ft_eq_second(delta, tab[0], tab[1], tab[2]));
	if (tmp < 0.0001)
		return (0);
	return (tmp);
}
