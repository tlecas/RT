/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 22:20:06 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:01:11 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int i;
	int nega;
	int result;

	result = 0;
	i = 0;
	nega = 1;
	while ((str[i] >= 9 && (str[i] <= 13)) || (str[i] == 32))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		nega = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while ((str[i] != '\0') && (ft_isdigit(str[i])))
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (nega * result);
}
