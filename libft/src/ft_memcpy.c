/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 00:32:28 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:05:54 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tab;
	const char	*tabs;
	size_t		i;

	tab = dst;
	tabs = src;
	i = 0;
	while (i < n)
	{
		tab[i] = tabs[i];
		i++;
	}
	return (dst);
}
