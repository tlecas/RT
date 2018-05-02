/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:24:29 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 21:21:45 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float					flmax(float reflet, float f)
{
	if (reflet < f)
		return (f);
	return (reflet);
}

static float			ft_cos_a(t_thread *thr, t_light *light)
{
	float	cos_a;
	float	intensity;

	light->prod_scal = dot(light->vect, thr->internorm);
	light->norm_l = norm(light->vect);
	light->norm_obj = norm(thr->internorm);
	intensity = fclamp((light->intensity / powf(light->norm_l, 2)), 0.0f, 1.0f);
	cos_a = -1.0f;
	if (light->norm_l * light->norm_obj != 0.0f)
		cos_a = (light->prod_scal / (light->norm_l * light->norm_obj))
				* intensity * thr->mat.diffuse;
	return (cos_a);
}

static void				rgb_addl(unsigned int *color, unsigned int d,
										t_thread *thr)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	filtbw;

	*color <<= 8;
	r = (*color >> 24) + d;
	uiclamp(&r, 0, 255);
	*color <<= 8;
	g = (*color >> 24) + d;
	uiclamp(&g, 0, 255);
	*color <<= 8;
	b = (*color >> 24) + d;
	uiclamp(&b, 0, 255);
	if (thr->keys & BLACK)
	{
		filtbw = (r + g + b) / 3;
		*color = (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		*color = (r << 16) + (g << 8) + b;
}

unsigned int			ft_light(t_thread *thr, t_light *light,
								unsigned int tmp)
{
	unsigned int	color;
	float			cos_a;
	t_vect			reflet;
	t_vect			cam;
	float			spec;

	color = tmp;
	light->vect = vectsub(light->pos, thr->interpos);
	if (ft_is_shadow(thr, light))
		return (0x00000000);
	if ((cos_a = ft_cos_a(thr, light)) < 0.0001f)
		return (0x00000000);
	rgb_mult(&color, cos_a, thr);
	reflet = vectsub(vmult(vmult(thr->internorm, dot(thr->internorm,
						light->vect)), 2.0f), light->vect);
	reflet = normalize(reflet);
	cam = vectsub(thr->e->cam->pos, thr->interpos);
	cam = normalize(cam);
	spec = powf(flmax(dot(reflet, cam), 0.0f), 100.0f) * 100.0f;
	if (spec > 0.0f)
		rgb_addl(&color, (unsigned int)(spec * thr->mat.specular
					* fclamp((light->intensity
					/ powf(light->norm_l, 2)), 0.0f, 1.0f)), thr);
	return (color);
}
