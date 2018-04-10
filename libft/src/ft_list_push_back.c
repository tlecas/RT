/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/23 18:07:15 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 16:06:11 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_list_push_back(t_list **begin_list, void *data)
{
	t_list *new_el;

	if (data != NULL)
	{
		if (*begin_list != NULL)
		{
			ft_putendl("dodo la saumur");
			new_el = *begin_list;
			while (new_el->next)
			{
				new_el = new_el->next;
			}
			new_el->next = ft_lstnew(data, sizeof(data));
			new_el = *begin_list;
		}
		else
		{
			new_el = ft_lstnew(data, sizeof(data));
			*begin_list = new_el;
		}
	}
}
