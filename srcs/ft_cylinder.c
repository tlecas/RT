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

/*void			ft_save_inter_cylinder(t_thread *thr, t_cylinder *cylinder, t_ray *ray)
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
		thr->internorm = normalize(vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f));
}

void			ft_post_cylinder(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->cylinder[i]->radius;
	thr->pos = thr->e->cylinder[i]->pos;
	thr->axis = thr->e->cylinder[i]->axis;
	ft_save_inter_cylinder(thr, thr->e->cylinder[i], &thr->ray);
	*tmp = thr->e->cylinder[i]->color;
}*/

void			ft_post_cylinder(t_thread *thr, unsigned int *tmp)
{
	int		i;
	float	m;

	i = thr->number;
	thr->ar = thr->e->cylinder[i]->radius;
	thr->pos = thr->e->cylinder[i]->pos;
	thr->axis = thr->e->cylinder[i]->axis;
	thr->interpos = vectadd(thr->ray.pos, vmult(thr->ray.dir, thr->value));
	m = dot(thr->ray.dir, thr->axis) * thr->value + dot(thr->ray.pos, thr->axis);
	thr->internorm = normalize(vectsub(vectsub(thr->interpos, thr->pos), vmult(thr->axis, m)));
	if (!(thr->e->cylinder[i]->mat.refraction > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	*tmp = thr->e->cylinder[i]->color;
}

float			ft_calc_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vect	pos;
	float	tmp;

	if (!norm2(cylinder->axis))
		cylinder->axis = coord_v(0.0f, 1.0f, 0.0f);
	cylinder->axis = normalize(cylinder->axis);
	pos = vectsub(ray->pos, cylinder->pos);
	a = dot(ray->dir, ray->dir) - dot(ray->dir, cylinder->axis) * dot(ray->dir, cylinder->axis);
	b = 2.0f * (dot(pos, ray->dir) - dot(ray->dir, cylinder->axis) * dot(pos, cylinder->axis));
	c = dot(pos, pos) - dot(pos, cylinder->axis) * dot(pos, cylinder->axis) - (cylinder->radius * cylinder->radius);
	delta = b * b - 4.0f * a * c;
	tmp = ft_eq_second(delta, a, b, c);
	if (tmp < 0.0001f)
		return (0);
	return (tmp);
}
