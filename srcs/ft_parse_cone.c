/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:41:39 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 03:45:27 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bool	ft_fill_properties2(t_cone *cone, char *str)
{
	if (!(ft_strncmp(str, "\tangle: ", 8)))
		cone->angle = ft_atof_free(ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "\tambient: ", 10)))
		cone->mat.ambient = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tdiffuse: ", 10)))
		cone->mat.diffuse = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tspecular: ", 11)))
		cone->mat.specular = ft_atof_free(ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "\treflection: ", 13)))
		cone->mat.reflection = ft_atof_free(ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\trefraction: ", 13)))
		cone->mat.refraction = ft_atof_free(ft_strrcpy(str, 13));
	else
		return (0);
	return (1);
}

static int		ft_fill_properties(t_cone *cone, char *str)
{
	char	*tmp;
	char	*test;

	if (ft_fill_properties2(cone, str))
		(void)tmp;
	else if (!(ft_strncmp(str, "\tcolor: ", 8)))
	{
		errno = 0;
		cone->color = strtol(
			tmp = ft_strrcpy(str, 8), &test, 16);
		free(tmp);
		if ((errno == ERANGE && (cone->color == UINT_MAX || cone->color == 0))
			|| (errno != 0 && cone->color == 0) || '\0' != *test)
			ft_error("Invalid color", 0, 0);
	}
	else
		return (0);
	return (1);
}

static int		ft_fill_coords(t_cone *cone, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		cone->pos.x = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		cone->pos.y = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		cone->pos.z = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\taxisX: ", 8)))
		cone->axis.x = ft_atof_free(ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "\taxisY: ", 8)))
		cone->axis.y = ft_atof_free(ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "\taxisZ: ", 8)))
		cone->axis.z = ft_atof_free(ft_strrcpy(str, 8));
	else
		return (0);
	return (1);
}

static t_cone	*ft_parse_properties(t_cone *cone, char *str)
{
	if (str && str[0] == '\t')
	{
		if ((!ft_fill_coords(cone, str)) && (!ft_fill_properties(cone, str)))
			ft_error("Can't parse properties of an object", 0, 0);
		return (cone);
	}
	return (0);
}

int				ft_parse_cone(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		incone;

	i = -1;
	j = -1;
	incone = 0;
	if (!(e->cone = ft_memalloc(sizeof(t_cone *) * (e->objnb->cone + 1))))
		ft_error("error malloc", 0, 0);
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "cone:"))
		{
			++j;
			e->cone[j] = ft_init_cone(e->cone[j]);
			incone = 1;
		}
		else if (incone == 1 && tab[i][0] == '\t')
			e->cone[j] = ft_parse_properties(e->cone[j], tab[i]);
		else if (tab[i][0] != '\t')
			incone = 0;
	}
	return (0);
}
