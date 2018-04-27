/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eq_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:57:08 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/27 06:19:05 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float		ft_eq_second(float delta, float a, float b, float c)
{
	float	s1;
	float	s2;
	float	q;

	if (!delta)
	{
		s1 = -b / (2 * a);
		s2 = s1;
	}
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(delta)) : -0.5 * (b - sqrt(delta));
		s1 = q / a;
		s2 = c / q;
	}
	if (s1 > 0 && s2 > 0)
		return ((s1 > s2) ? s2 : s1);
	else
		return (0);
}
