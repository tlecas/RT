/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:15:43 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/27 07:01:00 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam		*ft_init_camera(t_cam *cam)
{
	if (!(cam = malloc(sizeof(t_cam))))
		ft_error("Error malloc!");
	cam->pos = coord_v(0.0f, 0.0f, 0.0f);
	cam->angle = coord_v(0.0f, 0.0f, 0.0f);
	cam->dir = coord_v(0.0f, 0.0f, 0.0f);
	return (cam);
}

static int		ft_fill_coords(t_cam *cam, char *str)
{
	char	*tmp;

	if (!(ft_strncmp(str, "\tx: ", 4)))
		cam->pos.x = ft_atof(tmp = ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\ty: ", 4)))
		cam->pos.y = ft_atof(tmp = ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tz: ", 4)))
		cam->pos.z = ft_atof(tmp = ft_strrcpy(str, 4));
	else if (!(ft_strncmp(str, "\tangle_x: ", 10)))
		cam->angle.x = ft_atof(tmp = ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tangle_y: ", 10)))
		cam->angle.y = ft_atof(tmp = ft_strrcpy(str, 10));
	else if (!(ft_strncmp(str, "\tangle_z: ", 10)))
		cam->angle.z = ft_atof(tmp = ft_strrcpy(str, 10));
	else
		return (0);
	free(tmp);
	return (1);
}

static t_cam		*ft_parse_properties(t_cam *cam, char *str)
{
	if (str[0] == '\t')
	{
		if ((!ft_fill_coords(cam, str)))
			ft_error("Can't parse properties of an object");
		return (cam);
	}
	return (0);
}

int		ft_parse_camera(t_env *e, char **tab)
{
	int		i;
	int		incam;

	i = -1;
	incam = 0;
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "camera:"))
		{
			e->cam = ft_init_camera(e->cam);
			incam = 1;
		}
		else if (incam == 1 && tab[i][0] == '\t')
			e->cam = ft_parse_properties(e->cam, tab[i]);
		else if (tab[i][0] != '\t')
			incam = 0;
	}
	return (0);
}
