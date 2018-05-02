/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:21:31 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:45:51 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_light				*ft_init_light(t_light *light)
{
	if (!(light = malloc(sizeof(t_light))))
		ft_error("Error malloc'ing!");
	light->pos = coord_v(0, 0, 0);
	light->intensity = 1.0;
	light->color = 0x00FFFFFF;
	return (light);
}

static int			ft_fill_properties(t_light *light, char *str)
{
	char	*tmp;
	char	*test;

	if (!(ft_strncmp(str, "\tintensity: ", 12)))
		light->intensity = ft_atof_free(ft_strrcpy(str, 12));
	else if (!(ft_strncmp(str, "\tcolor: ", 8)))
	{
		errno = 0;
		light->color = strtol(
			tmp = ft_strrcpy(str, 8), &test, 16);
		free(tmp);
		if ((errno == ERANGE && (light->color == UINT_MAX || light->color == 0))
			|| (errno != 0 && light->color == 0) || '\0' != *test)
		{
			ft_error("Invalid color");
		}
	}
	else
		return (0);
	if (light->intensity < 0.0)
		light->intensity = 0.0;
	return (1);
}

static int			ft_fill_coords(t_light *light, char *str)
{
	if (!(ft_strncmp(str, "\tx: ", 4)))
		light->pos.x = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		light->pos.y = ft_atof_free(ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		light->pos.z = ft_atof_free(ft_strrcpy(str, 4));
	else
		return (0);
	return (1);
}

static t_light		*ft_parse_properties(t_light *light, char *str)
{
	if (str && str[0] == '\t')
	{
		if ((!ft_fill_coords(light, str)) && (!ft_fill_properties(light, str)))
			ft_error("Can't parse properties of an object");
		return (light);
	}
	return (0);
}

int					ft_parse_light(t_env *e, char **tab)
{
	int		i;
	int		j;
	int		inlight;

	i = -1;
	j = -1;
	inlight = 0;
	if (!(e->light = ft_memalloc(sizeof(t_light *) * (e->objnb->light + 1))))
		ft_error("error malloc");
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "light:"))
		{
			++j;
			e->light[j] = ft_init_light(e->light[j]);
			inlight = 1;
		}
		else if (inlight == 1 && tab[i][0] == '\t')
			e->light[j] = ft_parse_properties(e->light[j], tab[i]);
		else if (tab[i][0] != '\t')
			inlight = 0;
	}
	return (0);
}
