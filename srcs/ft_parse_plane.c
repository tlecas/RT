/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:37:22 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 17:44:49 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_bool		ft_fill_properties2(t_plane *plane, char *str)
{
	char	*test;
	char	*tmp;

	if (!(ft_strncmp(str, "\tcolor: ", 8)))
	{
		errno = 0;
		plane->color = strtol(
			tmp = ft_strrcpy(str, 8), &test, 16);
		free(tmp);
		if ((errno == ERANGE && (plane->color == UINT_MAX || plane->color == 0))
			|| (errno != 0 && plane->color == 0) || '\0' != *test)
			ft_error("Invalid color", 0, 0);
	}
	else if (!(ft_strncmp(str, "\tdiffuse: ", 10)))
		plane->mat.diffuse = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tspecular: ", 11)))
		plane->mat.specular = ft_atof_free(ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "\treflection: ", 13)))
		plane->mat.reflection = ft_atof_free(ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\trefraction: ", 13)))
		plane->mat.refraction = ft_atof_free(ft_strrcpy(str, 13));
	else
		return (0);
	return (1);
}

static int			ft_fill_properties(t_plane *plane, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (!(ft_strncmp(str, "\tambient: ", 10)))
		plane->mat.ambient = ft_atof_free(ft_strrcpy(str, 10));
	else if (ft_fill_properties2(plane, str))
		(void)tmp;
	else if (!(ft_strncmp(str, "\ttexture: ", 10)))
	{
		tmp = ft_strrcpy(str, 10);
		if (!(ft_strncmp(tmp, "checker", 7)))
			plane->checker = 1;
		else
			lodepng_decode32_file(&(plane->tx),
				&(plane->t_w), &(plane->t_h), tmp);
	}
	else
		return (0);
	free(tmp);
	return (1);
}

static int			ft_fill_coords(t_plane *plane, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		plane->pos.x = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		plane->pos.y = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		plane->pos.z = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tnormalX: ", 10)))
		plane->normal.x = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tnormalY: ", 10)))
		plane->normal.y = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tnormalZ: ", 10)))
		plane->normal.z = ft_atof_free(ft_strrcpy(str, 10));
	else
		return (0);
	return (1);
}

static t_plane		*ft_parse_properties(t_plane *plane, char *str)
{
	if (str && str[0] == '\t')
	{
		if (!(ft_fill_coords(plane, str)) &&
			(!(ft_fill_properties(plane, str))))
			ft_error("Can't parse properties of an object", 0, 0);
		return (plane);
	}
	return (0);
}

int					ft_parse_plane(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		inplane;

	i = -1;
	j = -1;
	inplane = 0;
	if (!(e->plane = ft_memalloc(sizeof(t_plane *) * (e->objnb->plane + 1))))
		ft_error("error malloc", 0, 0);
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "plane:"))
		{
			++j;
			if (!(e->plane[j] = ft_memalloc(sizeof(t_plane))))
				ft_error("Error malloc!", 0, 0);
			inplane = 1;
		}
		else if (inplane == 1 && tab[i][0] == '\t')
			e->plane[j] = ft_parse_properties(e->plane[j], tab[i]);
		else if (tab[i][0] != '\t')
			inplane = 0;
	}
	return (0);
}
