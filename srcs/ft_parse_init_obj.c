/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_init_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:32:28 by mprevot           #+#    #+#             */
/*   Updated: 2018/05/02 12:32:30 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cylinder		*ft_init_cylinder(t_cylinder *cylinder)
{
	if (!(cylinder = malloc(sizeof(t_cylinder))))
		ft_error("Error malloc");
	cylinder->pos = coord_v(0, 0, 0);
	cylinder->axis = coord_v(0, 0, 0);
	cylinder->radius = 1.0;
	cylinder->color = 0xFF00FF00;
	cylinder->mat = ft_mat_init();
	cylinder->inter = 0;
	return (cylinder);
}

t_para			*ft_init_para(t_para *para)
{
	if (!(para = malloc(sizeof(t_para))))
		ft_error("Error malloc!");
	para->pos = coord_v(0.0f, 0.0f, 0.0f);
	para->normal = coord_v(0.0f, 0.0f, 0.0f);
	para->k = 0;
	para->color = 0x0000FFFF;
	para->mat = ft_mat_init();
	para->inter = 0;
	return (para);
}

t_sphere		*ft_init_sphere(t_sphere *sphere)
{
	if (!(sphere = malloc(sizeof(t_sphere))))
		ft_error("Error malloc'ing!");
	sphere->pos = coord_v(0.0f, 0.0f, 0.0f);
	sphere->mat = ft_mat_init(0.0f, 0.0f, 0.0f);
	sphere->radius = 1.0f;
	sphere->color = 0x000000FF;
	sphere->inter = 0.0f;
	return (sphere);
}
