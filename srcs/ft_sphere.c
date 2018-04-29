/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:10:01 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/28 23:57:01 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_save_inter_sphere(t_thread *thr, t_sphere *sphere, t_ray *ray)
{
	thr->interpos = vectadd(ray->pos, vmult(ray->dir, thr->value));
	thr->internorm = normalize(vectsub(thr->interpos, sphere->pos));
	if (!(sphere->mat.refraction) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * 0.1f) + 1.0f); // surface rugueuse
}

void			ft_post_sphere(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->sphere[i]->radius;
	thr->pos = thr->e->sphere[i]->pos;
	thr->rotate = thr->e->sphere[i]->rotate;
	ft_save_inter_sphere(thr, thr->e->sphere[i], &thr->ray);
	*tmp = thr->e->sphere[i]->color;
}

float ft_calc_sphere(t_sphere *sphere, t_ray *ray)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vect	pos;

	pos = vectsub(ray->pos, sphere->pos);
	a = dot(ray->dir, ray->dir);
	b = 2.0f * dot(pos, ray->dir);
	c = dot(pos, pos) - (sphere->radius * sphere->radius);
	delta = b * b - 4.0f * a * c;
	return (ft_eq_second(delta, a, b, c));
}
