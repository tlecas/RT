/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:10:01 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:46:15 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_save_inter_sphere(t_thread *thr, t_sphere *sphere, t_camera *camera)
{
	thr->interpos = vectadd(camera->pos, vmult(camera->v, thr->value));
	thr->internorm = vectsub(thr->interpos, sphere->pos);
	if (!(sphere->mat.refraction) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f); // surface rugueuse
}

void			ft_post_sphere(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->sphere[i]->radius;
	thr->pos = thr->e->sphere[i]->pos;
	thr->rotate = thr->e->sphere[i]->rotate;
	ft_save_inter_sphere(thr, thr->e->sphere[i], &thr->cam);
	*tmp = thr->e->sphere[i]->color;
}

static float	ft_calc_inter_sphere(t_vect pos, t_vect vect, t_sphere *sphere)
{
	float	a;
	float	b;
	float	c;
	float	delta;

	delta = 0.0f;
	a = norm2(vect);
	b = (dot(pos, vect)) * 2.0f;
	c = (norm2(pos)) - (sphere->radius * sphere->radius);
	delta = (b * b) - (4.0f * a * c);
	if (delta < 0.0001f)
		return (0);
	else
		return (ft_eq_second(delta, a, b));
}

float ft_calc_sphere(t_sphere *sphere, t_camera *camera)
{
	t_vect pos;
	t_vect vect;

	sphere->inter = 0;
	pos = vrotate(vectsub(camera->pos, sphere->pos), sphere->rotate);
	vect = vrotate(camera->v, sphere->rotate);
	if ((sphere->inter = ft_calc_inter_sphere(pos, vect, sphere)) < 0.00001f)
		return (0);
	return (sphere->inter);
}
