/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 07:53:08 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:05:56 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tab1;
	unsigned char	*tab2;

	tab1 = (unsigned char*)s1;
	tab2 = (unsigned char*)s2;
	i = 0;
	while (i < n && tab1[i] == tab2[i])
		i++;
	if (i == n)
		return (0);
	return (tab1[i] - tab2[i]);
}
