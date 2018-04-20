/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:17:16 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:46:12 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	fresnel(t_thread *thr)
{
	float	kr;
	float	cosi;
	float	etai;
	float	sint;
	float	cost;
	float	rs;
	float	rp;
	float	refraction;

	etai = 1;
	refraction = thr->mat.refraction;
	cosi = fclamp(dot(thr->internorm, thr->cam.v), -1.0, 1.0);
	if (cosi > 0)
	{
		sint = etai;
		etai = refraction;
		refraction = sint;
	}
	sint = etai / refraction * sqrt(fclamp((1 - cosi * cosi), 0, 400000));
	if (sint >= 1.00)
		kr = 1.00;
	else
	{
		cost = sqrt(fclamp((1 - sint * sint), 0, 400000));
		cosi = ABS(cosi);
		rs = ((refraction * cosi) - (etai * cost)) / ((refraction * cosi) + (etai * cost));
		rp = ((etai * cosi) - (refraction * cost)) / ((etai * cosi) + (refraction * cost));
		kr = (rs * rs + rp * rp) / 2.0;
	}
	return (kr);
}

t_vect	refracted2(t_thread *thr)
{
	float			refraction;
	float			cosi;
	float			etai;
	float			eta;
	float			k;
	t_vect			v;

	etai = 1;
	v = thr->internorm;
	refraction = thr->mat.refraction;
	cosi = fclamp(dot(thr->internorm, thr->cam.v), -1.0f, 1.0f);
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		eta = refraction;
		refraction = etai;
		etai = eta;
		v = vmult(v, -1);
	}
	eta = etai / refraction;
	k = 1.0f - eta * eta * (1.0f - cosi * cosi);
	return (k < 0.0f ? coord_v(0, 0, 0) : vectadd(vmult(thr->cam.v, eta), vmult(v, (eta * cosi -  sqrt(k)))));
}

unsigned int	refracted(t_thread *thr, unsigned int color, float kr)
{
	unsigned int	tmp;
	float			refraction;

	tmp = 0;
	refraction = thr->mat.refraction;
	thr->cam.pos = thr->interpos;
	thr->cam.v = refracted2(thr);
	thr->cam.v = normalize(thr->cam.v);
	tmp = ft_calc_obj(thr, (thr->recursivity - 1));
	rgb_mult(&color, (1 - refraction), thr);
	if(thr->value > 0.0001f)
	{
		rgb_mult(&tmp, (1 - kr), thr);
		rgb_add(&color, tmp, thr);
	}
	return (color);
}

unsigned int	reflected(t_thread *thr, unsigned int color, float kr)
{
	unsigned int	tmp;
	float			reflection;

	tmp = 0;
	reflection = thr->mat.reflection;
	thr->cam.pos = thr->interpos;
	thr->cam.v = vectsub(thr->cam.v, vmult(vmult(thr->internorm, dot(thr->internorm, thr->cam.v)), 2));
	thr->cam.v = normalize(thr->cam.v);
	tmp = ft_calc_obj(thr, (thr->recursivity - 1));
	rgb_mult(&color, (1 - reflection), thr);
	if (thr->value > 0.0001f)
	{
		rgb_mult(&tmp, kr, thr);
		rgb_add(&color, tmp, thr);
	}
	return(color);
}
