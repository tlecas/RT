/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rt.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmachena <gmachena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:52:38 by gmachena          #+#    #+#             */
/*   Updated: 2018/03/29 18:21:45 by gmachena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int g_x;
int g_y;

unsigned int ft_calc_obj(t_thread *thr, int recursivity)
{
	double	obj[thr->e->objnb->totobj];
	int		i;
	int		j;
//	unsigned int color;

	j = 0;
	i = 0;
	thr->recursivity = recursivity;
	while (thr->e->objnb->sphere != 0 && i < thr->e->objnb->sphere)
	{
		obj[i] = ft_calc_sphere(thr->e->sphere[i], &thr->cam);
		i++;
	}
	j = i;
	while (thr->e->objnb->plane != 0 && (i - j) < thr->e->objnb->plane)
	{
		obj[i] = ft_calc_plan(thr->e->plane[i - j], &thr->cam);
		i++;
	}
	j = i;
	while (thr->e->objnb->cylinder != 0 && (i - j) < thr->e->objnb->cylinder)
	{
		obj[i] = ft_calc_cylinder(thr->e->cylinder[i - j], &thr->cam);
		i++;
	}
	j = i;
	while (thr->e->objnb->cone != 0 && (i - j) < thr->e->objnb->cone)
	{
		obj[i] = ft_calc_cone(thr->e->cone[i - j], &thr->cam);
		i++;
	}
	i = ft_isview(obj, i - 1);
	return (ft_load_post(thr, i, obj[i]));
}

void ft_calc_ray(int i, int j, t_thread *thr)
{
	double x;
	double y;
	double z;
	double fov;

	fov = (thr->e->diaphragm * (M_PI / 180));
	x = (i - (thr->WIN_X / 2.0));
	y = ((thr->WIN_Y / 2.0) - j);
	z = (thr->WIN_X / (tan(fov / 2.0) * 2.0));
	thr->cam.v = vrotate(normalize(coord_v(x, y, z)), thr->e->camera->angle);
	thr->cam.pos = thr->e->camera->pos;
	thr->cam.angle = thr->e->camera->angle;
}

void *thread_rt(void *arg)
{
	int			i;
	int			nbr_pxl;
	t_thread	*thr;

	thr = (t_thread *)arg;
	i = thr->tid;
	nbr_pxl = thr->WIN_X * thr->WIN_Y;
	while (i < nbr_pxl)
	{
		g_x = (i % thr->WIN_X);
		g_y = (i / thr->WIN_X);
		thr->recursivity = thr->e->recursivity;
		ft_calc_ray((i % thr->WIN_X), (i / thr->WIN_X), thr);
		thr->color = ft_calc_obj(thr, thr->recursivity);
		//printf("///thr->colory = 0x%08x\n", thr->color);
		//printf("i = %d\n", i);
		//if (i == 328394)
		//	while(1);
		ft_print_obj(thr, (i % thr->WIN_X), (i / thr->WIN_X));
		i = i + THREADS;
	}
	pthread_exit(NULL);
}

void	ft_rt(t_env *e)
{
	pthread_t	thread[THREADS];
	int			i;
	int			rc;
	t_thread	thr[THREADS];

	i = -1;
	while (++i < THREADS)
	{
		thr[i].tid = i;
		thr[i].e = e; 
		if ((rc = pthread_create(&thread[i], NULL, thread_rt, &thr[i])))
			return ;
	}
	i = -1;
	while (++i < THREADS)
		pthread_join(thread[i], NULL);
	
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}
