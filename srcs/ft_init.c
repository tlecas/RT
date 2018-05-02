/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 17:38:05 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 21:17:16 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_env	*ft_init_obj_nb(t_env *e)
{
	if (!(e->objnb = malloc(sizeof(t_objnb))))
		ft_error("Error malloc!", 0, 0);
	e->objnb->sphere = 0;
	e->objnb->cylinder = 0;
	e->objnb->cone = 0;
	e->objnb->para = 0;
	e->objnb->light = 0;
	e->objnb->plane = 0;
	e->objnb->totobj = 0;
	return (e);
}

t_env			*ft_load_obj(t_env *e, char **tab)
{
	ft_parse_sphere(e, tab);
	ft_parse_plane(e, tab);
	ft_parse_para(e, tab);
	ft_parse_light(e, tab);
	ft_parse_cone(e, tab);
	ft_parse_cylinder(e, tab);
	ft_parse_camera(e, tab);
	return (e);
}

void			ft_init_env(t_env *e)
{
	e->win = mlx_new_window(e->mlx, WIN_X, WIN_Y, "RT");
	e->img = mlx_new_image(e->mlx, WIN_X, WIN_Y);
	e->win_area = (WIN_X * WIN_Y);
	e->tmpaddr = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian);
	e->data = (int *)e->tmpaddr;
	e->t_ratio = 10.0f;
	e->t_x = 500.0f;
	e->t_y = 500.0f;
	e->c_ratio = 1.0f;
	e->screenshot = 0;
}

void		ft_checksubvalues(t_env *e)
{
	int i = 0;

	while (e->plane[i])
	{
		if (e->plane[i]->mat.ambient < 0 || e->plane[i]->mat.ambient > 1)
			ft_error("ambient dans plane", 0, 0);
		if (e->plane[i]->mat.diffuse < 0 || e->plane[i]->mat.diffuse > 1)
			ft_error("diffuse dans plane", 0, 0);
		if (e->plane[i]->mat.specular < 0 || e->plane[i]->mat.specular > 20)
			ft_error("specular dans plane", 0, 0);
		if (e->plane[i]->mat.reflection < 0 || e->plane[i]->mat.reflection > 1)
			ft_error("reflection dans plane", 0, 0);
		if (e->plane[i]->mat.refraction != 0 && (e->plane[i]->mat.refraction < 1 || e->plane[i]->mat.refraction > 2.5))
			ft_error("refraction dans plane", 0, 0);
		i++;
	}
	i = 0;
	while (e->cone[i])
	{
		if (e->cone[i]->angle < 0 || e->cone[i]->angle > 90)
			ft_error("angle dans cone", 0, 0);
		if (e->cone[i]->mat.ambient < 0 || e->cone[i]->mat.ambient > 1)
			ft_error("ambient dans cone", 0, 0);
		if (e->cone[i]->mat.diffuse < 0 || e->cone[i]->mat.diffuse > 1)
			ft_error("diffuse dans cone", 0, 0);
		if (e->cone[i]->mat.specular < 0 || e->cone[i]->mat.specular > 20)
			ft_error("specular dans cone", 0, 0);
		if (e->cone[i]->mat.reflection < 0 || e->cone[i]->mat.reflection > 1)
			ft_error("reflection dans cone", 0, 0);
		if (e->plane[i]->mat.refraction != 0 && (e->plane[i]->mat.refraction < 1 || e->plane[i]->mat.refraction > 2.5))
			ft_error("refraction dans cone", 0, 0);
		i++;

	}
	i = 0;
	while (e->cylinder[i])
	{
		if (!(e->cylinder[i]->radius > 0))
			ft_error("cylinder dans cylinder", 0, 0);
		if (e->cylinder[i]->mat.ambient < 0 || e->cylinder[i]->mat.ambient > 1)
			ft_error("ambient dans cylinder", 0, 0);
		if (e->cylinder[i]->mat.diffuse < 0 || e->cylinder[i]->mat.diffuse > 1)
			ft_error("diffuse dans cylinder", 0, 0);
		if (e->cylinder[i]->mat.specular < 0 || e->cylinder[i]->mat.specular > 20)
			ft_error("specular dans cylinder", 0, 0);
		if (e->cylinder[i]->mat.reflection < 0 || e->cylinder[i]->mat.reflection > 1)
			ft_error("reflection dans cylinder", 0, 0);
		if (e->plane[i]->mat.refraction != 0 && (e->plane[i]->mat.refraction < 1 || e->plane[i]->mat.refraction > 2.5))
			ft_error("refraction dans cylinder", 0, 0);
		i++;
	}
	i = 0;
	while (e->sphere[i])
	{
		if (e->sphere[i]->radius < 0)
			ft_error("sphere dans sphere", 0, 0);
		if (e->sphere[i]->mat.ambient < 0 || e->sphere[i]->mat.ambient > 1)
			ft_error("ambient dans sphere", 0, 0);
		if (e->sphere[i]->mat.diffuse < 0 || e->sphere[i]->mat.diffuse > 1)
			ft_error("diffuse dans sphere", 0, 0);
		if (e->sphere[i]->mat.specular < 0 || e->sphere[i]->mat.specular > 20)
			ft_error("specular dans sphere", 0, 0);
		if (e->sphere[i]->mat.reflection < 0 || e->sphere[i]->mat.reflection > 1)
			ft_error("reflection dans sphere", 0, 0);
		if (e->plane[i]->mat.refraction != 0 && (e->plane[i]->mat.refraction < 1 || e->plane[i]->mat.refraction > 2.5))
			ft_error("refraction dans sphere", 0, 0);
		i++;
	}
	i = 0;
}

void		ft_checkvalues(t_env *e)
{
	if (e->width < 300 || e->width > 4000)
		ft_error("Width value error", 0, 0);
	if (e->height < 300 || e->height > 4000)
		ft_error("Width value error", 0, 0);
	if (e->recursivity < 0 || e->recursivity >= 42)
		ft_error("Recursivity value error", 0, 0);
	if (e->fov >= 180 || e->fov <= 45)
		ft_error("Fov value error", 0, 0);
	if (e->ambient_light > 1)
		ft_error("Ambient light value error", 0, 0);
	ft_checksubvalues(e);
}

t_env		*ft_init(char *filename)
{
	t_env		*e;
	char		**tab;
	int			i;

	i = -1;
	(void)tab;
	if (!(e = malloc(sizeof(t_env))))
		ft_error("malloc error", 0, 0);
	e->keys = 0;
	if (!(e->mlx = mlx_init()))
	{
		free(e);
		ft_error("mlx_init error", 0, 0);
	}
	e = ft_init_obj_nb(e);
	if (!(e->filename = malloc(sizeof(char) * (ft_strlen(filename) + 1))))
		ft_error("malloc error", 0, 0);
	e->filename = ft_strcpy(e->filename, filename);
	tab = ft_parse_file(e);
	e = ft_load_obj(e, tab);
	ft_init_env(e);
	while (tab[++i])
		free(tab[i]);
	free(tab);
	ft_checkvalues(e);
	return (e);
}
