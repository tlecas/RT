/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_filters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 04:43:50 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/03 04:43:56 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_check_filters(t_env *e)
{
	if (e->keys & CARTOON)
		ft_cartoon_filter(e);
	if (e->keys & SEPIA)
		ft_sepia_filter(e);
	if (e->keys & BLACK)
		ft_black_filter(e);
}
