/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 01:49:25 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 01:49:43 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_error(char *str, void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	ft_putendl(str);
	exit(EXIT_FAILURE);
}
