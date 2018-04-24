/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cuboid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprevot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 13:05:56 by mprevot           #+#    #+#             */
/*   Updated: 2018/04/24 13:06:03 by mprevot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cuboid		*ft_init_cuboid(t_cuboid *cuboid)
{
	if (!(cuboid = ft_memalloc(sizeof(t_cuboid))))
		ft_error("Error malloc");
	cuboid->pos = coord_v(0, 0, 0);
	cuboid->rotate = coord_v(0, 0, 0);
	//cuboid->radius = 1.0;
	cuboid->color = 0xFF00FF00;
	cuboid->mat = ft_mat_init();
	cuboid->inter = 0;

	return (cuboid);
}

static int		ft_fill_properties(t_cuboid *cuboid, char *str)
{
	char	*tmp;
	char	*test;

	/*if (!(ft_strncmp(str, "\tradius: ", 9)))
		cuboid->radius = ft_atof(tmp = ft_strrcpy(str, 9));
	else */if (!(ft_strncmp(str, "\tcolor: ", 8)))
	{
		errno = 0;
		cuboid->color = strtol(tmp = ft_strrcpy(str, 8), &test, 16);
		if ((errno == ERANGE && (cuboid->color == UINT_MAX || cuboid->color == 0))
            || (errno != 0 && cuboid->color == 0) || '\0' != *test)
		{
			ft_error("Invalid color");
		}
	}
	else if (!(ft_strncmp(str, "\tambient: ", 10)))
		cuboid->mat.ambient = ft_atof(tmp = ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tdiffuse: ", 10)))
		cuboid->mat.diffuse = ft_atof(tmp = ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tspecular: ", 11)))
		cuboid->mat.specular = ft_atof(tmp = ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "\treflection: ", 13)))
		cuboid->mat.reflection = ft_atof(tmp = ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\trefraction: ", 13)))
		cuboid->mat.refraction = ft_atof(tmp = ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\theight: ", 9)))
		cuboid->height = ft_atof(tmp = ft_strrcpy(str, 9));
	else if (!(ft_strncmp(str, "\twidth: ", 8)))
		cuboid->width = ft_atof(tmp = ft_strrcpy(str, 8));
	else if (!(ft_strncmp(str, "\tdept: ", 7)))
		cuboid->dept = ft_atof(tmp = ft_strrcpy(str, 7));
	else
		return (0);
	free(tmp);
	return (1);
}

static int		ft_fill_coords(t_cuboid *cuboid, char *str)
{
	char	*tmp;

	if (!(ft_strncmp(str, "\tx: ", 4)))
		cuboid->pos.x = ft_atof(tmp = ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		cuboid->pos.y = ft_atof(tmp = ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		cuboid->pos.z = ft_atof(tmp = ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\trotX: ", 7)))
		cuboid->rotate.x = ft_atof(tmp = ft_strrcpy(str, 7));
	else if (!(ft_strncmp(str, "\trotY: ", 7)))
		cuboid->rotate.y = ft_atof(tmp = ft_strrcpy(str, 7));
	else if (!(ft_strncmp(str, "\trotZ: ", 7)))
		cuboid->rotate.z = ft_atof(tmp = ft_strrcpy(str, 7));
	else
		return (0);
	free(tmp);
	return (1);
}

static t_cuboid		*ft_parse_properties(t_cuboid *cuboid, char *str)
{
	if (str && str[0] == '\t')
	{
		if ((!ft_fill_coords(cuboid, str)) && (!ft_fill_properties(cuboid, str)))
			ft_error("Can't parse properties of an object");
		return (cuboid);
	}
	return (0);
}

int		ft_parse_cuboid(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		incuboid;

	i = -1;
	j = -1;
	incuboid = 0;
	if (!(e->cuboid = malloc(sizeof(t_cuboid *) * (e->objnb->cuboid))))
		ft_error("error malloc");
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "cuboid:"))
		{
			++j;
			e->cuboid[j] = ft_init_cuboid(e->cuboid[j]);
			incuboid = 1;
		}
		else if (incuboid == 1 && tab[i][0] == '\t')
			e->cuboid[j] = ft_parse_properties(e->cuboid[j], tab[i]);
		else if (tab[i][0] != '\t')
			incuboid = 0;
	}
	return (0);
}
