/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 17:31:09 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:01:09 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_after_dot(const char *str)
{
	double			nbr;
	unsigned int	div;

	div = 10;
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr += (*str - '0') / (double)div;
		div *= 10;
		str++;
	}
	return (nbr);
}

double			ft_atof(const char *str)
{
	double			nbr;
	int				isnegative;

	nbr = 0;
	while (ft_iswp(*str))
		str++;
	isnegative = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = 10 * nbr + *str - '0';
		str++;
	}
	if (*str == '.')
		nbr += get_after_dot(++str);
	nbr *= isnegative;
	return (nbr);
}

double			ft_atof_free(char *str)
{
	double value;

	value = ft_atof(str);
	free(str);
	return (value);
}
