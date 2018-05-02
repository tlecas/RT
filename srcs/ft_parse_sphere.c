/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 14:46:06 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 02:51:12 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_bool			ft_fill_properties2(t_sphere *sphere, char *str)
{
	if (!(ft_strncmp(str, "\tambient: ", 10)))
		sphere->mat.ambient = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tdiffuse: ", 10)))
		sphere->mat.diffuse = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tspecular: ", 11)))
		sphere->mat.specular = ft_atof_free(ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "\treflection: ", 13)))
		sphere->mat.reflection = ft_atof_free(ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\trefraction: ", 13)))
		sphere->mat.refraction = ft_atof_free(ft_strrcpy(str, 13));
	else
		return (0);
	return (1);
}

static int		ft_fill_properties(t_sphere *sphere, char *str)
{
	char	*tmp;
	char	*test;

	tmp = NULL;
	if (!(ft_strncmp(str, "\tradius: ", 9)))
		sphere->radius = ft_atof_free(ft_strrcpy(str, 9));
	else if (!(ft_strncmp(str, "\tcolor: ", 8)))
	{
		errno = 0;
		sphere->color = strtol(
			tmp = ft_strrcpy(str, 8), &test, 16);
		if ((errno == ERANGE &&
			(sphere->color == UINT_MAX || sphere->color == 0))
			|| (errno != 0 && sphere->color == 0) || '\0' != *test)
		{
			ft_error("Invalid color", 0, 0);
		}
	}
	else if (ft_fill_properties2(sphere, str))
		(void)tmp;
	else
		return (0);
	free(tmp);
	return (1);
}

static int		ft_fill_coords(t_sphere *sphere, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		sphere->pos.x = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		sphere->pos.y = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		sphere->pos.z = ft_atof_free(ft_strrcpy(str, 4));
	else
		return (0);
	return (1);
}

static t_sphere	*ft_parse_properties(t_sphere *sphere, char *str)
{
	if (str && str[0] == '\t')
	{
		if ((!ft_fill_coords(sphere, str)) &&
			(!ft_fill_properties(sphere, str)))
			ft_error("Can't parse properties of an object", 0, 0);
		return (sphere);
	}
	return (0);
}

int				ft_parse_sphere(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		insphere;

	i = -1;
	j = -1;
	insphere = 0;
	if (!(e->sphere = ft_memalloc(sizeof(t_sphere *) * (e->objnb->sphere + 1))))
		ft_error("error malloc", 0, 0);
	while (tab[++i])
	{
		if (!(ft_strcmp(tab[i], "sphere:")))
		{
			++j;
			e->sphere[j] = ft_init_sphere(e->sphere[j]);
			insphere = 1;
		}
		else if (insphere == 1 && tab[i][0] == '\t')
			e->sphere[j] = ft_parse_properties(e->sphere[j], tab[i]);
		else if (tab[i][0] != '\t')
			insphere = 0;
	}
	return (0);
}
