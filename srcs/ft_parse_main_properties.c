/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_main_properties.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:08:17 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:45:52 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_parse_main_properties(t_env *e, char *str)
{
	char	*tmp;

	if (!(ft_strncmp(str, "width: ", 7)))
		e->width = ft_atoi(tmp = ft_strrcpy(str, 7));
	else if (!(ft_strncmp(str, "height: ", 8)))
		e->height = ft_atoi(tmp = ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "recursivity: ", 13)))
		e->recursivity = ft_atoi(tmp = ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "antialias: ", 11)))
		e->antialias = ft_strequ("true", tmp = ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "diaphragm: ", 11)))
		e->diaphragm = ft_atof(tmp = ft_strrcpy(str, 11));
	else
		return (-1);
	free(tmp);
	return (1);
}
