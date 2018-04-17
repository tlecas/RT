/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 18:30:37 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:45:42 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_save_inter_cylinder(t_thread *thr, t_cylinder *cylinder, t_camera *camera)
{
	t_vect	norm;
	float	dotc;

	dotc = 0.0f;
	norm = vrotateinv(coord_v(0.0f, 1.0f, 0.0f), cylinder->rotate);
	thr->interpos = vectadd(camera->pos, vmult(camera->v, thr->value));
	thr->internorm = vectsub(thr->interpos, cylinder->pos);
	dotc = dot(norm, thr->internorm);
	thr->internorm = vectsub(thr->internorm, vmult(norm, dotc));
	thr->internorm = normalize(thr->internorm);
}

void			ft_post_cylinder(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->cylinder[i]->radius;
	thr->pos = thr->e->cylinder[i]->pos;
	thr->rotate = thr->e->cylinder[i]->rotate;
	ft_save_inter_cylinder(thr, thr->e->cylinder[i], &thr->cam);
	*tmp = thr->e->cylinder[i]->color;
}

static float	ft_calc_inter_cylinder(t_cylinder *cylinder, t_vect pos, t_vect vect)
{
	float a;
	float b;
	float c;
	float delta;

	a = vect.x * vect.x + vect.z * vect.z;
	b = (pos.x * vect.x) * 2.0f + (pos.z * vect.z) * 2.0f;
	c = (pos.x * pos.x) + (pos.z * pos.z) - (cylinder->radius * cylinder->radius);
	delta = (b * b) - (4.0f * a * c);
	if (delta < 0.0f)
		return (0);
	else
		return (ft_eq_second(delta, a, b));
}

float	ft_calc_cylinder(t_cylinder *cylinder, t_camera *camera)
{
	t_vect	pos;
	t_vect	vect;

	cylinder->inter = 0.0f;
	pos = vrotate(vectsub(camera->pos, cylinder->pos), cylinder->rotate);
	vect = vrotate(camera->v, cylinder->rotate);
	if ((cylinder->inter = ft_calc_inter_cylinder(cylinder, pos, vect)) < 0.0001f)
		return (0);
	return (cylinder->inter);
}
