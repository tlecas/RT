/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:02:36 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:46:07 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	ft_save_inter_plan(t_thread *thr, t_plane *plane, t_camera *camera)
{
	thr->internorm = coord_v(0.0f, 1.0f, 0.0f);
	thr->interpos = vectadd(camera->pos, vmult(camera->v, thr->value));
	thr->internorm = vrotateinv(thr->internorm, plane->rotate);
}

void			ft_post_plane(t_thread *thr, unsigned int *tmp)
{
	int	i;

	i = thr->number;
	thr->pos = thr->e->plane[i]->pos;
	thr->rotate = thr->e->plane[i]->rotate;
	ft_save_inter_plan(thr, thr->e->plane[i], &thr->cam);
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
