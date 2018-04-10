/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 07:30:56 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:05:58 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tab;

	i = -1;
	tab = (unsigned char*)s;
	while (++i < n)
		if (tab[i] == (unsigned char)c)
		{
			tab = &tab[i];
			return (tab);
		}
	return (0);
}
