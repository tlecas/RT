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

int g_y;
int g_x;


void	ft_save_inter_sphere(t_thread *thr, t_sphere *sphere, t_camera *camera)
{
	//debug("rotate", rot);
	thr->interpos = vectadd(camera->pos, vmult(camera->v, thr->value));
	thr->internorm = vectsub(thr->interpos, sphere->pos);
	//thr->internorm = normalize(thr->internorm);
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

static double	ft_calc_inter_sphere(t_vect pos, t_vect vect, t_sphere *sphere)
{
	double	a;
	double	b;
	double	c;
	double	delta;

	delta = 0;
	a = norm2(vect);
	b = (dot(pos, vect)) * 2.0;
	c = (norm2(pos)) - (sphere->radius * sphere->radius);
	delta = (b * b) - (4.0 * a * c);
	if (delta < 0.0001)
		return (0);
	else
		return (ft_eq_second(delta, a, b));
}

double ft_calc_sphere(t_sphere *sphere, t_camera *camera)
{
	t_vect pos;
	t_vect vect;

	sphere->inter = 0;
	pos = vrotate(vectsub(camera->pos, sphere->pos), sphere->rotate);
	vect = vrotate(camera->v, sphere->rotate);
	if ((sphere->inter = ft_calc_inter_sphere(pos, vect, sphere)) < 0.0001)
		return (0);
	return (sphere->inter);
}
