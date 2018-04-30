/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 13:01:31 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 03:49:56 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int g_x;
int g_y;

int		ft_shadow_sphere(t_thread *thr, int i, t_ray *shadow_eye)
{
	t_sphere	shadow_sphere;
	float			j;

	j = 0.0f;
	shadow_sphere.pos = thr->e->sphere[i]->pos;
	shadow_sphere.radius = thr->e->sphere[i]->radius;
	j = ft_calc_sphere(&shadow_sphere, shadow_eye);
	if (j > 0.0001f && j <= 1.0f)
		return (1);
	return (0);
}

int		ft_shadow_cone(t_thread *thr, int i, t_ray *shadow_eye)
{
	t_cone	shadow_cone;
	float			j;

	j = 0.0f;
	shadow_cone.pos = thr->e->cone[i]->pos;
	shadow_cone.axis = thr->e->cone[i]->axis;
	shadow_cone.angle = thr->e->cone[i]->angle;
	j = ft_calc_cone(&shadow_cone, shadow_eye);
	if (j > 0.0001f && j <= 1.0f)
		return (1);
	return (0);
}

int		ft_shadow_cylinder(t_thread *thr, int i, t_ray *shadow_eye)
{
	t_cylinder	shadow_cylinder;
	float			j;

	j = 0.0f;
	shadow_cylinder.pos = thr->e->cylinder[i]->pos;
	shadow_cylinder.axis = thr->e->cylinder[i]->axis;
	shadow_cylinder.radius = thr->e->cylinder[i]->radius;
	j = ft_calc_cylinder(&shadow_cylinder, shadow_eye);
	if (j > 0.0001f && j <= 1.0f)
		return (1);
	return (0);
}
