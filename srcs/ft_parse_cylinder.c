/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:52:22 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 03:10:21 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bool		ft_fill_properties2(t_cylinder *cylinder, char *str)
{
	if (!(ft_strncmp(str, "\tambient: ", 10)))
		cylinder->mat.ambient = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tdiffuse: ", 10)))
		cylinder->mat.diffuse = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tspecular: ", 11)))
		cylinder->mat.specular = ft_atof_free(ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "\treflection: ", 13)))
		cylinder->mat.reflection = ft_atof_free(ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\trefraction: ", 13)))
		cylinder->mat.refraction = ft_atof_free(ft_strrcpy(str, 13));
	else
		return (0);
	return (1);
}

static int			ft_fill_properties(t_cylinder *cylinder, char *str)
{
	char	*tmp;
	char	*test;

	if (!(ft_strncmp(str, "\tradius: ", 9)))
		cylinder->radius = ft_atof_free(ft_strrcpy(str, 9));
	else if (!(ft_strncmp(str, "\tcolor: ", 8)))
	{
		errno = 0;
		cylinder->color = strtol(
			tmp = ft_strrcpy(str, 8), &test, 16);
		free(tmp);
		if ((errno == ERANGE && (cylinder->color == UINT_MAX ||
			cylinder->color == 0))
			|| (errno != 0 && cylinder->color == 0) || '\0' != *test)
			ft_error("Invalid color", 0, 0);
	}
	else if (ft_fill_properties2(cylinder, str))
		(void)tmp;
	else
		return (0);
	return (1);
}

static int			ft_fill_coords(t_cylinder *cylinder, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		cylinder->pos.x = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		cylinder->pos.y = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		cylinder->pos.z = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\taxisX: ", 8)))
		cylinder->axis.x = ft_atof_free(ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "\taxisY: ", 8)))
		cylinder->axis.y = ft_atof_free(ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "\taxisZ: ", 8)))
		cylinder->axis.z = ft_atof_free(ft_strrcpy(str, 8));
	else
		return (0);
	return (1);
}

static t_cylinder	*ft_parse_properties(t_cylinder *cylinder, char *str)
{
	if (str && str[0] == '\t')
	{
		if ((!ft_fill_coords(cylinder, str)) &&
			(!ft_fill_properties(cylinder, str)))
			ft_error("Can't parse properties of an object", 0, 0);
		return (cylinder);
	}
	return (0);
}

int					ft_parse_cylinder(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		incylinder;

	i = -1;
	j = -1;
	incylinder = 0;
	if (!(e->cylinder = ft_memalloc(sizeof(t_cylinder *) *
		(e->objnb->cylinder + 1))))
		ft_error("error malloc", 0, 0);
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "cylinder:"))
		{
			++j;
			e->cylinder[j] = ft_init_cylinder(e->cylinder[j]);
			incylinder = 1;
		}
		else if (incylinder == 1 && tab[i][0] == '\t')
			e->cylinder[j] = ft_parse_properties(e->cylinder[j], tab[i]);
		else if (tab[i][0] != '\t')
			incylinder = 0;
	}
	return (0);
}
