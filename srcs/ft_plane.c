/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:36 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 02:49:31 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int		plane_checker(t_thread *thr, t_vect e_1, t_vect e_2)
{
	float			t_1;
	float			t_2;

	t_1 = thr->e->c_ratio * dot(e_1, vectsub(thr->interpos, thr->pos));
	t_2 = thr->e->c_ratio * dot(e_2, vectsub(thr->interpos, thr->pos));
	if ((t_1 >= 0.0f && t_2 >= 0.0f) || (t_1 < 0.0f && t_2 < 0.0f))
	{
		if (((int)t_1 % 2 == 0 && (int)t_2 % 2 == 0) || ((abs((int)t_1 % 2) == 1
			&& abs((int)t_2 % 2) == 1)))
			return (0x00000000);
		else
			return (0x00FFFFFF);
	}
	else
	{
		if (((int)t_1 % 2 == 0 && (int)t_2 % 2 == 0) || ((abs((int)t_1 % 2) == 1
			&& abs((int)t_2 % 2) == 1)))
			return (0x00FFFFFF);
		else
			return (0x00000000);
	}
}

unsigned int		plane_texture(t_thread *thr, t_vect e_1, t_vect e_2, int i)
{
	float			t_1;
	float			t_2;
	unsigned int	tmp;

	t_1 = thr->e->t_ratio * dot(e_1, vectsub(thr->interpos, thr->pos))
		+ thr->e->t_x;
	t_2 = thr->e->t_ratio * dot(e_2, vectsub(thr->interpos, thr->pos))
		+ thr->e->t_y;
	if (thr->e->plane[i]->tx && t_1 >= 0.0f && t_2 >= 0.0f && (int)t_1 <
		(int)thr->e->plane[i]->t_w && (int)t_2 < (int)thr->e->plane[i]->t_h)
	{
		tmp = 0x00000000;
		tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w +
			(int)t_1) * 4] << 16;
		tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w +
			(int)t_1) * 4 + 1] << 8;
		tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w +
			(int)t_1) * 4 + 2];
		return (tmp);
	}
	else
		return (thr->e->plane[thr->number]->color);
}

unsigned int		plane_tx(t_thread *thr, t_vect u, int i)
{
	t_vect			e_1;
	t_vect			e_2;

	if (u.x == 0 && u.y == 0)
	{
		e_1 = coord_v(1.0f, 0.0f, 0.0f);
		e_2 = coord_v(0.0f, 1.0f, 0.0f);
	}
	else
	{
		e_1 = normalize(coord_v(-(u.y), u.x, 0.0f));
		e_2 = normalize(coord_v(((-(u.x)) * u.z), ((-(u.y)) * u.z),
			(u.x * u.x + u.y * u.y)));
	}
	if (thr->e->plane[i]->checker)
		return (plane_checker(thr, e_1, e_2));
	else
		return (plane_texture(thr, e_1, e_2, i));
}

void				ft_post_plane(t_thread *thr, unsigned int *tmp)
{
	int				i;

	i = thr->number;
	thr->pos = thr->e->plane[i]->pos;
	thr->normal = thr->e->plane[i]->normal;
	thr->interpos = vectadd(thr->ray.pos, vmult(thr->ray.dir, thr->value));
	if (dot(thr->normal, thr->ray.dir) > 0.0f)
	{
		thr->internorm.x = -(thr->normal.x);
		thr->internorm.y = -(thr->normal.y);
		thr->internorm.z = -(thr->normal.z);
	}
	else
		thr->internorm = thr->normal;
	if (!(thr->e->plane[i]->mat.refraction > .1 ||
		thr->e->plane[i]->mat.reflection > .1) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f);
	if (thr->e->plane[i]->tx || thr->e->plane[i]->checker)
		*tmp = plane_tx(thr, thr->internorm, i);
	else
		*tmp = thr->e->plane[i]->color;
}

float				ft_calc_plan(t_plane *plane, t_ray *ray)
{
	float			inter;
	float			tmp;

	if (!norm2(plane->normal))
		plane->normal = coord_v(0.0f, 1.0f, 0.0f);
	plane->normal = normalize(plane->normal);
	tmp = dot(plane->normal, ray->dir);
	if (fabsf(tmp) < 0.0001f)
		return (0.0f);
	inter = -(dot(plane->normal, vectsub(ray->pos, plane->pos))) / tmp;
	if (inter < 0.00001f)
		return (0);
	return (inter);
}
