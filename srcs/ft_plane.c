/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:36 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 03:23:20 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_save_inter_plan(t_thread *thr, t_plane *plane, t_ray *ray)
{
	thr->interpos = vectadd(ray->pos, vmult(ray->dir, thr->value));
	if (dot(thr->normal, ray->dir) > 0.0f)
	{
		thr->internorm.x = -(thr->normal.x);
		thr->internorm.y = -(thr->normal.y);
		thr->internorm.z = -(thr->normal.z);
	}
	else
		thr->internorm = thr->normal;
	if (!(plane->mat.refraction || plane->mat.reflection) && (thr->e->keys & ROUGH))
		thr->internorm = normalize(vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f)); // surface rugueuse
}

void			ft_post_plane(t_thread *thr, unsigned int *tmp)
{
	int		i;
	float	t_1;
	float	t_2;
	t_vect	e_1;
	t_vect	e_2;
	t_vect	u;

	i = thr->number;
	thr->e->plane[i]->chess = 0;
	thr->pos = thr->e->plane[i]->pos;
	thr->normal = thr->e->plane[i]->normal;
	ft_save_inter_plan(thr, thr->e->plane[i], &thr->ray);
	if (thr->e->plane[i]->tx || thr->e->plane[i]->chess)
	{
		u = thr->internorm;
		e_1 = normalize(coord_v(-(u.y), u.x, 0.0f));
		e_2 = normalize(coord_v(((-(u.x)) * u.z),((-(u.y)) * u.z), (u.x * u.x + u.y * u.y)));
		t_1 = thr->e->t_ratio * dot(e_1, vectsub(thr->interpos, thr->pos)) + thr->e->t_x;
		t_2 = thr->e->t_ratio * dot(e_2, vectsub(thr->interpos, thr->pos)) + thr->e->t_y;
		if (thr->e->plane[i]->chess)
		{
			if (((int)t_1 % 2 == 0 && (int)t_2 % 2 == 0) || (((int)t_1 % 2 == 1 && (int)t_2 % 2 == 1)))
				*tmp = 0x00000000;
			else
				*tmp = 0x00FFFFFF;
		}
		if (thr->e->plane[i]->tx && t_1 >= 0.0f && t_2 >= 0.0f && (int)t_1 < (int)thr->e->plane[i]->t_w && (int)t_2 < (int)thr->e->plane[i]->t_h)
		{
			*tmp = 0x00000000;
			*tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w + (int)t_1) * 4] << 16;
			*tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w + (int)t_1) * 4 + 1] << 8;
			*tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w + (int)t_1) * 4 + 2] ;
		}
	}
	else
		*tmp = thr->e->plane[i]->color;
}

float		ft_calc_plan(t_plane *plane, t_ray *ray)
{
	float	inter;
	float	tmp;

	if (!norm2(plane->normal))
		plane->normal = coord_v(0.0f, 1.0f, 0.0f);
	plane->normal = normalize(plane->normal);
	tmp = dot(plane->normal, ray->dir);
	if (fabsf(tmp) < 0.0001f)
		return (0.0f);
	inter = -(dot(plane->normal, vectsub(ray->pos, plane->pos))) / tmp;
	if (inter > 0.0f)
		return (inter);
	return (0.0f);
}
