/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:24:29 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:45:46 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static float		ft_cos_a(t_thread *thr, t_light *light)
{
	float	cos_a;
	float	intensity;

	light->prod_scal = dot(light->vect, thr->internorm);
	light->norm_l = norm(light->vect);
	light->norm_obj = norm(thr->internorm);
	intensity = fclamp((light->intensity / POW2(light->norm_l)), 0.0f, 1.0f);
	cos_a = -1.0f;
	if (light->norm_l * light->norm_obj != 0.0f)
		cos_a = (light->prod_scal / (light->norm_l * light->norm_obj)) * intensity * thr->mat.diffuse;
	return (cos_a);
}


static void				rgb_addf(unsigned int *color, unsigned int d, t_thread *thr)
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
	if (thr->keys & 0x00000001)
	{
		filtbw = (r + g + b) / 3;
		*color = (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		*color = (r << 16) + (g << 8) + b;
}

float				flmax(float reflet, float f)
{
	if (reflet < f)
		return (f);
	return (reflet);
}

unsigned int		ft_light(t_thread *thr, t_light *light, unsigned int tmp)
{
	unsigned int	color;
	float			cos_a;
	t_vect			reflet;
	t_vect			cam;
	float			spec;


	color = tmp;
	light->vect = vectsub(light->pos, thr->interpos);
	if(ft_is_shadow(thr, light))
		return (0xFF000000);
	if ((cos_a = ft_cos_a(thr, light)) < 0.00001f)
		return(0xFF000000);
	rgb_mult(&color, cos_a, thr);
	reflet = vectsub(vmult(vmult(thr->internorm, dot(thr->internorm, light->vect)), 2.0f), light->vect);
	reflet = normalize(reflet);
	cam = vectsub(thr->e->camera->pos, thr->interpos);
	cam = normalize(cam);
	spec = pow(flmax(dot(reflet, cam), 0.0f), 500.0f) * 500.0f;
	if (spec > 0.0f)
		rgb_addf(&color, (unsigned int)(spec * thr->mat.specular 
					* fclamp((light->intensity / POW2(light->norm_l)), 0.0f, 1.0f)), thr);
	return (color);
}
