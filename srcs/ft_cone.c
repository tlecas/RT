/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 11:10:19 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 06:17:45 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*void		ft_save_inter_cone(t_thread *thr, t_cone *cone, t_ray *ray)
{
	t_vect	norm;
	double	dotc;

	dotc = 0.0;
	norm = vrotate(coord_v(0.0, 1.0, 0.0), cone->rotate);
	thr->interpos = vectadd(ray->pos, vmult(ray->dir, thr->value));
	thr->internorm = vectsub(thr->interpos, cone->pos);
	dotc = ddot(norm, thr->internorm);
	thr->internorm = vectsub(thr->internorm, vmult(norm, dotc));
	thr->internorm = normalize(thr->internorm);
	if (!(cone->mat.refraction) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f); // surface rugueuse
}*/

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
	m = dot(thr->ray.dir, thr->axis) * thr->value + dot(thr->ray.pos, thr->axis);
	k = tan(thr->ar * (M_PI / 180));
	thr->internorm = normalize(vectsub(vectsub(thr->interpos, thr->pos), vmult(vmult(thr->axis, (1 + k * k)), m)));
	if (!(thr->e->cone[i]->mat.refraction) && (thr->e->keys & ROUGH))
		thr->internorm = normalize(vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f));
	*tmp = thr->e->cone[i]->color;
}

/*void		ft_post_cone(t_thread *thr, unsigned int *tmp)
{
	int		i;
	float	rad;
	float	VopD;
	float	rDopD;
	float	m;
	t_vect	V;
	t_vect	axis_v;

	i = thr->number;
	thr->ar = thr->e->cone[i]->angle * (M_PI / 180.0);
	thr->pos = thr->e->cone[i]->pos;
	thr->rotate = thr->e->cone[i]->rotate;
	thr->interpos = vectadd(thr->ray.pos, vmult(thr->ray.dir, thr->value));
	axis_v = vrotate(coord_v(0.0f, 1.0f, 0.0f), thr->rotate);
	V = vectsub(thr->interpos, thr->pos);
	rad = 1 * thr->ar * thr->ar;
	VopD = dot(V, axis_v);
	rDopD = dot(thr->ray.dir, axis_v);
	m = rDopD * thr->value + VopD;
	thr->internorm = normalize(vectsub(V, vmult(axis_v, rad * m)));
	if (!(thr->e->cone[i]->mat.refraction) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	*tmp = thr->e->cone[i]->color;
}*/

/*double		ft_calc_cone(t_cone *cone, t_ray *ray)
{
	t_vect	axis_v;
	double	a;
	double	b;
	double	c;
	t_vect	pos;
	double	delta;
	double	tmp;

	axis_v = vrotate(coord_v(0.0f, 1.0f, 0.0f), cone->rotate);
	pos = vectsub(ray->pos, cone->pos);
	tmp = ddot(ray->dir, axis_v);
	a = pow(tmp, 2) - pow(cos(cone->angle * (M_PI / 180.0)), 2);
	b = 2.0 * (tmp * ddot(pos, axis_v) - ddot(ray->dir, pos) * pow(cos(cone->angle * (M_PI / 180.0)), 2));
	c = pow(ddot(pos, axis_v), 2) - ddot(pos, pos) * pow(cos(cone->angle * (M_PI / 180.0)), 2);
	delta = b * b - 4.0 * a * c;
	tmp = (ft_eq_second(delta, a, b, c));
	if (tmp < 0.01)
		return (0);
	return (tmp);
}*/

double		ft_calc_cone(t_cone *cone, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	t_vect	pos;
	double	delta;
	double	tmp;
	double	k;

	if (!norm2(cone->axis))
		cone->axis = coord_v(0.0f, 1.0f, 0.0f);
	cone->axis = normalize(cone->axis);
	pos = vectsub(ray->pos, cone->pos);
	k = tan(cone->angle * (M_PI / 180));
	a = dot(ray->dir, ray->dir) - (1 + k * k) * pow(dot(ray->dir, cone->axis), 2);
	b = 2.0f * (dot(pos, ray->dir) - (1 + k * k) * dot(ray->dir, cone->axis) * dot(pos, cone->axis));
	c = dot(pos, pos) - (1 + k * k) * pow(dot(pos, cone->axis), 2);
	delta = b * b - 4.0 * a * c;
	tmp = (ft_eq_second(delta, a, b, c));
	if (tmp < 0.0001)
		return (0);
	return (tmp);
}
