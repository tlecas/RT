/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moretools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 06:13:03 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 06:16:23 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int			ambient_light(t_thread *thr, unsigned int color)
{
	unsigned int		ambient;
	unsigned int		tab[3];
	unsigned int		tmp;
	float				doto;

	doto = fclamp((dot(vmult(thr->ray.dir, -1),
					thr->internorm) + 0.0 * 0.15), 0, 1);
	tmp = color;
	ambient = 0x00FFFFFF;
	tmp <<= 8;
	ambient <<= 8;
	tab[0] = uimin((ambient >> 24), (tmp >> 24)) * thr->mat.ambient * doto;
	uiclamp(&tab[0], 0, 255);
	tmp <<= 8;
	ambient <<= 8;
	tab[1] = uimin((ambient >> 24), (tmp >> 24)) * thr->mat.ambient * doto;
	uiclamp(&tab[1], 0, 255);
	uimin(tab[1], (tmp >> 24));
	tmp <<= 8;
	ambient <<= 8;
	tab[2] = uimin((ambient >> 24), (tmp >> 24)) * thr->mat.ambient * doto;
	uiclamp(&tab[2], 0, 255);
	ambient = (tab[0] << 16) + (tab[1] << 8) + tab[2];
	return (ambient);
}

static	int				ft_which_obj_helper(t_thread *thr, int *i, char **name)
{
	int					hit;

	hit = 0;
	if (*i < thr->e->objnb->sphere)
	{
		*name = ft_strdup("sphere");
		thr->mat = thr->e->sphere[*i]->mat;
		hit = 1;
	}
	else if (*i < thr->e->objnb->sphere + thr->e->objnb->plane)
	{
		*name = ft_strdup("plane");
		*i -= thr->e->objnb->sphere;
		thr->mat = thr->e->plane[*i]->mat;
		hit = 1;
	}
	else if (*i < thr->e->objnb->sphere + thr->e->objnb->plane
			+ thr->e->objnb->cylinder)
	{
		*name = ft_strdup("cylinder");
		*i -= thr->e->objnb->sphere + thr->e->objnb->plane;
		thr->mat = thr->e->cylinder[*i]->mat;
		hit = 1;
	}
	return (hit);
}

char					*ft_which_obj(t_thread *thr, int *i)
{
	char				*name;

	name = NULL;
	if (!(ft_which_obj_helper(thr, i, &name)))
	{
		if (*i < thr->e->objnb->sphere + thr->e->objnb->plane
				+ thr->e->objnb->cylinder + thr->e->objnb->cone)
		{
			name = ft_strdup("cone");
			*i -= thr->e->objnb->sphere + thr->e->objnb->plane +
				thr->e->objnb->cylinder;
			thr->mat = thr->e->cone[*i]->mat;
		}
		else if (*i < thr->e->objnb->sphere + thr->e->objnb->plane
				+ thr->e->objnb->cylinder + thr->e->objnb->cone +
					thr->e->objnb->para)
		{
			name = ft_strdup("para");
			*i -= thr->e->objnb->sphere + thr->e->objnb->plane
				+ thr->e->objnb->cylinder + thr->e->objnb->cone;
			thr->mat = thr->e->para[*i]->mat;
		}
	}
	return (name);
}
