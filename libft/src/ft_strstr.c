/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 17:28:37 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:03:42 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(little);
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i])
	{
		if (big[i] == little[0])
		{
			big = &big[i];
			if ((ft_strncmp(big, little, j)) == 0)
				return ((char*)big);
			i = 1;
		}
		else
			i++;
	}
	return (0);
}
