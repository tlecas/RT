/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 07:19:28 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:03:40 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*tab;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(tab = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while ((i < len) && s[start + i])
	{
		*(tab + i) = *(s + (start + i));
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
