/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 06:30:51 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:05:50 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void const *src, size_t n)
{
	size_t	i;
	char	*tab_src;
	char	*tab_dst;

	i = -1;
	tab_src = (char*)src;
	tab_dst = (char*)dst;
	if (tab_src < tab_dst)
		while ((int)(--n) >= 0)
			tab_dst[n] = tab_src[n];
	else
		while (++i < n)
			tab_dst[i] = tab_src[i];
	return (dst);
}
