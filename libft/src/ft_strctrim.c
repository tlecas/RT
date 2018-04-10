/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 03:53:07 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:04:51 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strctrim(char const *s, char c)
{
	char	*tab;
	int		i;
	int		j;

	if (s == 0)
		return (0);
	i = 0;
	j = ft_strlen(s);
	while ((*(s + i) == c))
		i++;
	while ((*(s + (j - 1)) == c) && j > i)
		j--;
	tab = ft_strsub(s, i, (j - i));
	return (tab);
}
