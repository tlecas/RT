/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_para.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 21:30:30 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/01 22:28:39 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			ft_fill_properties(t_para *para, char *str)
{
	char	*tmp;
	char	*test;

	if (!(ft_strncmp(str, "\tambient: ", 10)))
		para->mat.ambient = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tcolor: ", 8)) && !(errno = 0))
	{
		para->color = strtol(
			tmp = ft_strrcpy(str, 8), &test, 16);
		free(tmp);
		if ((errno == ERANGE && (para->color == UINT_MAX || para->color == 0))
			|| (errno != 0 && para->color == 0) || '\0' != *test)
			ft_error("Invalid color");
	}
	else if (!(ft_strncmp(str, "\tdiffuse: ", 10)))
		para->mat.diffuse = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tspecular: ", 11)))
		para->mat.specular = ft_atof_free(ft_strrcpy(str, 11));
	else if (!(ft_strncmp(str, "\treflection: ", 13)))
		para->mat.reflection = ft_atof_free(ft_strrcpy(str, 13));
	else if (!(ft_strncmp(str, "\trefraction: ", 13)))
		para->mat.refraction = ft_atof_free(ft_strrcpy(str, 13));
	else
		return (0);
	return (1);
}

static int			ft_fill_coords(t_para *para, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		para->pos.x = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		para->pos.y = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		para->pos.z = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tnormalX: ", 10)))
		para->normal.x = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tnormalY: ", 10)))
		para->normal.y = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tnormalZ: ", 10)))
		para->normal.z = ft_atof_free(ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tscalar: ", 9)))
		para->k = ft_atof_free(ft_strrcpy(str, 9));
	else
		return (0);
	return (1);
}

static t_para		*ft_parse_properties(t_para *para, char *str)
{
	if (str && str[0] == '\t')
	{
		if (!(ft_fill_coords(para, str)) && (!(ft_fill_properties(para, str))))
			ft_error("Can't parse properties of an object");
		return (para);
	}
	return (0);
}

int					ft_parse_para(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		inpara;

	i = -1;
	j = -1;
	inpara = 0;
	if (!(e->para = ft_memalloc(sizeof(t_para *) * (e->objnb->para + 1))))
		ft_error("error malloc");
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "paraboloid:"))
		{
			++j;
			if (!(e->para[j] = ft_memalloc(sizeof(t_para))))
				ft_error("Error malloc!");
			inpara = 1;
		}
		else if (inpara == 1 && tab[i][0] == '\t')
			e->para[j] = ft_parse_properties(e->para[j], tab[i]);
		else if (tab[i][0] != '\t')
			inpara = 0;
	}
	return (0);
}
