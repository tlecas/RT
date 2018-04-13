/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 17:38:05 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/13 18:02:56 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	t_env *ft_init_obj_nb(t_env *e)
{
	if (!(e->objnb = malloc(sizeof(t_objnb))))
		ft_error("Error malloc!");
	e->objnb->sphere = 0;
	e->objnb->cylinder = 0;
	e->objnb->cone = 0;
	e->objnb->light = 0;
	e->objnb->plane = 0;
	e->objnb->totobj = 0;
	return (e);
}

static		t_env *ft_init_eye(t_env *e)
{
	e->virt_e.pos = coord_v(0, 0, 0);
	e->virt_e.angle = coord_v(0, 0, 0);
	e->virt_e.v = coord_v(0, 0, 0);
	return (e);
}

t_env		*ft_load_obj(t_env *e, char **tab)
{
	ft_parse_sphere(e, tab);
	ft_parse_plane(e, tab);
	ft_parse_light(e, tab);
	ft_parse_cone(e, tab);
	ft_parse_cylinder(e, tab);
	ft_parse_camera(e, tab);
	return (e);
}

t_env		*ft_init(char *filename)
{
	t_env		*e;
	char		**tab;
	int			i;

	i = -1;
	(void)tab;
	if (!(e = malloc(sizeof(t_env))))
		ft_error("malloc error");
	e->keys = 0;
	e->mlx = mlx_init();
	e = ft_init_obj_nb(e);
	if (!(e->filename = malloc(sizeof(char) * (ft_strlen(filename) + 1))))
		ft_error("malloc error");
	e->filename = ft_strcpy(e->filename, filename);
	tab = ft_parse_file(e);
	e = ft_load_obj(e, tab);
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "RT");
	e->img = mlx_new_image(e->mlx, WIN_X, WIN_Y);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian);
	e = ft_init_eye(e);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (e);
}
