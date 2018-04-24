/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cuboid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:24:32 by mprevot           #+#    #+#             */
/*   Updated: 2018/04/24 14:24:34 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* rien n'est fonctionnel là. Il faut tout coder */

void			ft_save_inter_cuboid(t_thread *thr, t_cuboid *cuboid, t_camera *camera)
{
	t_vect	norm;
	float	dotc;

	dotc = 0.0f;
	norm = vrotateinv(coord_v(0.0f, 1.0f, 0.0f), cuboid->rotate);
	thr->interpos = vectadd(camera->pos, vmult(camera->v, thr->value));
	thr->internorm = vectsub(thr->interpos, cuboid->pos);
	dotc = dot(norm, thr->internorm);
	thr->internorm = vectsub(thr->internorm, vmult(norm, dotc));
	thr->internorm = normalize(thr->internorm);
	if (!(cuboid->mat.refraction) && (thr->e->keys & ROUGH))
	thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f); 
}

void			ft_post_cuboid(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->cuboid[i]->radius;
	thr->pos = thr->e->cuboid[i]->pos;
	thr->rotate = thr->e->cuboid[i]->rotate;
	ft_save_inter_cuboid(thr, thr->e->cuboid[i], &thr->cam);
	*tmp = thr->e->cuboid[i]->color;
}

static float	ft_calc_inter_cuboid(t_cuboid *cuboid, t_vect pos, t_vect vect)
{
	float a;
	float b;
	float c;
	float delta;

	a = vect.x * vect.x + vect.z * vect.z;
	b = (pos.x * vect.x) * 2.0f + (pos.z * vect.z) * 2.0f;
	c = (pos.x * pos.x) + (pos.z * pos.z) - (cuboid->radius * cuboid->radius);
	delta = (b * b) - (4.0f * a * c);
	if (delta < 0.0f)
		return (0);
	else
		return (ft_eq_second(delta, a, b));
}

float	ft_calc_cuboid(t_cuboid *cuboid, t_camera *camera)
{
	t_vect	pos;
	t_vect	vect;

	cuboid->inter = 0.0f;
	pos = vrotate(vectsub(camera->pos, cuboid->pos), cuboid->rotate);
	vect = vrotate(camera->v, cuboid->rotate);
	if ((cuboid->inter = ft_calc_inter_cuboid(cuboid, pos, vect)) < 0.00001f)
		return (0);
	return (cuboid->inter);
}
