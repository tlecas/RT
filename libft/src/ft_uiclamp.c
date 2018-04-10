/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uiclamp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:28:04 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:03:32 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	uiclamp(unsigned int *ui, unsigned int min, unsigned int max)
{
	if (*ui > max)
		*ui = max;
	if (*ui < min)
		*ui = min;
}

void	iclamp(int *ui, int min, int max)
{
	if (*ui > max)
		*ui = max;
	if (*ui < min)
		*ui = min;
}
