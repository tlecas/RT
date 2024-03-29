/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:12:13 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:45:56 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_is_shape_named(char *str1, char *str2)
{
	if (!ft_strcmp(str1, str2))
		return (1);
	else
		return (0);
}

t_vect		*ft_parse_coords(t_vect *pos, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		pos->x = (float)(ft_atof_free(ft_strrcpy(str, 4)));
	if (!(ft_strncmp(str, "\ty: ", 4)))
		pos->y = (float)(ft_atof_free(ft_strrcpy(str, 4)));
	if (!(ft_strncmp(str, "\tz: ", 4)))
		pos->z = (float)(ft_atof_free(ft_strrcpy(str, 4)));
	if (!(ft_strncmp(str, "\trotX: ", 7)))
		pos->x = (float)(ft_atof_free(ft_strrcpy(str, 7)));
	if (!(ft_strncmp(str, "\trotY: ", 7)))
		pos->y = (float)(ft_atof_free(ft_strrcpy(str, 7)));
	if (!(ft_strncmp(str, "\trotZ: ", 7)))
		pos->z = (float)(ft_atof_free(ft_strrcpy(str, 7)));
	return (pos);
}
