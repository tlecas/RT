/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eq_second.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 09:57:08 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 18:24:27 by tlecas           ###   ########.fr       */
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
		s1 = -b / (2.0f * a);
		s2 = s1;
	}
	else
	{
		q = (b > 0.0f) ? -0.5f * (b + sqrt(delta)) : -0.5f * (b - sqrt(delta));
		s1 = q / a;
		s2 = c / q;
	}
	if (s1 > 0.0f && s2 > 0.0f)
		return ((s1 > s2) ? s2 : s1);
	else
		return (0.0f);
}
