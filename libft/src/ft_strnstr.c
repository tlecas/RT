/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 20:31:53 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:04:03 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i;
	size_t	j;
	int		z;

	i = 0;
	z = 0;
	j = ft_strlen(little);
	if (little[0] == '\0')
		return ((char*)big);
	while (big[i] && j <= len)
	{
		if (big[i] == little[0] && (j + z) <= len)
		{
			big = &big[i];
			if ((ft_strncmp(big, little, j)) == 0)
				return ((char*)big);
			i = 0;
		}
		i++;
		z++;
	}
	return (0);
}
