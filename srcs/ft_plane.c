/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:36 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/24 17:04:08 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	ft_save_inter_plan(t_thread *thr, t_plane *plane, t_camera *camera)
{
	thr->internorm = coord_v(0.0f, 1.0f, 0.0f);
	thr->interpos = vectadd(camera->pos, vmult(camera->v, thr->value));
	thr->internorm = vrotateinv(thr->internorm, plane->rotate);
	if (!(plane->mat.refraction || plane->mat.reflection) && (thr->e->keys & ROUGH))
		thr->internorm = vmult(thr->internorm, (sin(thr->x / 8) * .1f) + 1.0f); // surface rugueuse
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
	thr->pos = thr->e->plane[i]->pos;
	thr->rotate = thr->e->plane[i]->rotate;
	ft_save_inter_plan(thr, thr->e->plane[i], &thr->cam);
	if (thr->e->plane[i]->tx)
	{
		u = thr->internorm;
		e_1 = normalize(coord_v(-(u.y), u.x, 0));
		e_2 = normalize(coord_v(((-(u.x)) * u.z),((-(u.y)) * u.z), (u.x * u.x + u.y * u.y)));
		t_1 = thr->e->t_ratio * dot(e_1, vectsub(thr->interpos, thr->pos)) + thr->e->t_x;
		t_2 = thr->e->t_ratio * dot(e_2, vectsub(thr->interpos, thr->pos)) + thr->e->t_y;
		if (t_1 >= 0.0f && t_2 >= 0.0f && (int)t_1 < (int)thr->e->plane[i]->t_w && (int)t_2 < (int)thr->e->plane[i]->t_h)
		{
			*tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w + (int)t_1) * 4] << 16;
			*tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w + (int)t_1) * 4 + 1] << 8;
			*tmp += thr->e->plane[i]->tx[((int)t_2 * thr->e->plane[i]->t_w + (int)t_1) * 4 + 2] ;
		}
	}
	else
		*tmp = thr->e->plane[i]->color;
}

static float	ft_calc_inter_plan(t_vect pos, t_vect vect)
{
	float inter;

	inter = pos.y / vect.y;
	inter = -inter;
	if (inter < 0.0001f)
		return (0);
	return (inter);
}

float			ft_calc_plan(t_plane *plane, t_camera *camera)
{
		t_vect pos;
		t_vect vect;

		plane->inter = 0.0f;
		pos = vrotate(vectsub(camera->pos, plane->pos), plane->rotate);
		vect = vrotate(camera->v, plane->rotate);
		if ((ABS(vect.y)) < 0.0001f)
			return (0);
		plane->inter = ft_calc_inter_plan(pos, vect);
		return (plane->inter);
}
