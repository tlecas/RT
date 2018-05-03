/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 03:10:34 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 03:10:53 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_is_shadow(t_thread *thr, t_light *light)
{
	if (thr->name & SPHERE)
		return (ft_prepare_shadow_sphere(thr, light));
	else if (thr->name & PLANE)
		return (ft_prepare_shadow_plane(thr, light));
	else if (thr->name & CYL)
		return (ft_prepare_shadow_cylinder(thr, light));
	else if (thr->name & CONE)
		return (ft_prepare_shadow_cone(thr, light));
	else if (thr->name & PLANE)
		return (ft_prepare_shadow_para(thr, light));
	return (0);
}
