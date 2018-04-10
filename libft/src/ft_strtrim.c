/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 23:57:37 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:03:38 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*tab;
	int		i;
	int		j;

	if (s == 0)
		return (0);
	i = 0;
	j = ft_strlen(s);
	while (ft_iswp(*(s + i)))
		i++;
	while (ft_iswp(*(s + (j - 1))) && j > i)
		j--;
	tab = ft_strsub(s, i, (j - i));
	return (tab);
}
