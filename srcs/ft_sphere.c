/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 19:10:01 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 20:39:07 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_save_inter_sphere(t_thread *thr, t_sphere *sphere,
					t_ray *ray)
{
	thr->interpos = vectadd(ray->pos, vmult(ray->dir, thr->value));
	thr->internorm = normalize(vectsub(thr->interpos, sphere->pos));
	if (!(sphere->mat.refraction > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * 0.1f) + 1.0f);
}

void			ft_post_sphere(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->ar = thr->e->sphere[i]->radius;
	thr->pos = thr->e->sphere[i]->pos;
	ft_save_inter_sphere(thr, thr->e->sphere[i], &thr->ray);
	*tmp = thr->e->sphere[i]->color;
}

float			ft_calc_sphere(t_sphere *sphere, t_ray *ray)
{
	float	tab[3];
	float	delta;
	float	tmp;
	t_vect	pos;

	pos = vectsub(ray->pos, sphere->pos);
	tab[0] = dot(ray->dir, ray->dir);
	tab[1] = 2.0f * dot(pos, ray->dir);
	tab[2] = dot(pos, pos) - (sphere->radius * sphere->radius);
	delta = tab[1] * tab[1] - 4.0f * tab[0] * tab[2];
	tmp = ft_eq_second(delta, tab[0], tab[1], tab[2]);
	if (tmp < 0.0001f)
		return (0);
	return (tmp);
}
