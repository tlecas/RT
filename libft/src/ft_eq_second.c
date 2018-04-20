/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eq_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:57:08 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:02:58 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_eq_second(float delta, float a, float b)
{
	float inter1;
	float inter2;

	inter1 = 0;
	inter2 = 0;
	if (delta >= 0)
		inter1 = (-b - sqrt(delta)) / (2 * a);
	if (delta > 0)
	{
		inter2 = (-b + sqrt(delta)) / (2 * a);
		if (inter2 > 0 && inter2 < inter1)
			return (inter2);
	}
	return (inter1);
}
