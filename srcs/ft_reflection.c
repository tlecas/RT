/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reflection.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 16:17:16 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/27 05:53:05 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float			fresnel(t_thread *thr)
{
	float	tab[8];

	tab[2] = 1;
	tab[7] = thr->mat.refraction;
	tab[1] = fclamp(dot(thr->internorm, thr->ray.dir), -1.0, 1.0);
	if (tab[1] > 0)
	{
		tab[3] = tab[2];
		tab[2] = tab[7];
		tab[7] = tab[3];
	}
	tab[3] = tab[2] / tab[7] * sqrt(fclamp((1 - tab[1] * tab[1]), 0, 400000));
	if (tab[3] >= 1.00)
		tab[0] = 1.00;
	else
	{
		tab[4] = sqrt(fclamp((1 - tab[3] * tab[3]), 0, 400000));
		tab[1] = ABS(tab[1]);
		tab[5] = ((tab[7] * tab[1]) - (tab[2] * tab[4]))
			/ ((tab[7] * tab[1]) + (tab[2] * tab[4]));
		tab[6] = ((tab[2] * tab[1]) - (tab[7] * tab[4]))
			/ ((tab[2] * tab[1]) + (tab[7] * tab[4]));
		tab[0] = (tab[5] * tab[5] + tab[6] * tab[6]) / 2.0;
	}
	return (tab[0]);
}

t_vect			refracted2(t_thread *thr)
{
	float			refraction;
	float			cosi;
	float			eta[2];
	float			k;
	t_vect			v;

	eta[0] = 1;
	v = thr->internorm;
	refraction = thr->mat.refraction;
	cosi = fclamp(dot(thr->internorm, thr->ray.dir), -1.0f, 1.0f);
	if (cosi < 0)
		cosi = -cosi;
	else
	{
		eta[1] = refraction;
		refraction = eta[0];
		eta[0] = eta[1];
		v = vmult(v, -1);
	}
	eta[1] = eta[0] / refraction;
	k = 1.0f - eta[1] * eta[1] * (1.0f - cosi * cosi);
	return (k < 0.0f ? coord_v(0, 0, 0) : vectadd(vmult(thr->ray.dir, eta[1]),
					vmult(v, (eta[1] * cosi - sqrt(k)))));
}

unsigned int	refracted(t_thread *thr, unsigned int color, float kr)
{
	unsigned int	tmp;
	float			refraction;

	tmp = 0;
	refraction = thr->mat.refraction;
	thr->ray.pos = thr->interpos;
	thr->ray.dir = refracted2(thr);
	thr->ray.dir = normalize(thr->ray.dir);
	tmp = ft_calc_obj(thr, (thr->recursivity - 1));
	rgb_mult(&color, (1 - refraction), thr);
	if (thr->value > 0.0001f)
	{
		rgb_mult(&tmp, (1 - kr), thr);
		rgb_add(&color, tmp);
	}
	return (color);
}

unsigned int	reflected(t_thread *thr, unsigned int color, float kr)
{
	unsigned int	tmp;
	float			reflection;

	tmp = 0;
	reflection = thr->mat.reflection;
	thr->ray.pos = thr->interpos;
	thr->ray.dir = vectsub(thr->ray.dir,
			vmult(vmult(thr->internorm, dot(thr->internorm, thr->ray.dir)), 2));
	thr->ray.dir = normalize(thr->ray.dir);
	tmp = ft_calc_obj(thr, (thr->recursivity - 1));
	rgb_mult(&color, (1 - reflection), thr);
	if (thr->value > 0.0001f)
	{
		rgb_mult(&tmp, kr, thr);
		rgb_add(&color, tmp);
	}
	return (color);
}
