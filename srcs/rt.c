/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:52:38 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/10 15:48:22 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int ft_calc_obj(t_thread *thr, int recursivity)
{
	double	obj[thr->e->objnb->totobj];
	int		i;
	int		j;

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

void ft_calc_ray(float i, float j, t_thread *thr)
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
	int				i;
	t_thread		*thr;
	int				aa;
	int				n;
	unsigned int	tmp;


	thr = (t_thread *)arg;
	i = thr->tid;
	thr->keys = thr->e->keys;
	aa = (thr->keys & 0x00000002);
	n = aa;
	while (i < thr->WIN_X * thr->WIN_Y)
	{
		if (aa)
		{
			thr->recursivity = thr->e->recursivity;
			thr->color = 0;
			while (n-- > 0)
			{
			//	ft_calc_ray(i % thr->WIN_X, i / thr->WIN_X, thr);
				ft_calc_ray((i % thr->WIN_X) + (1.0 / aa * n) - 1.0, (i / thr->WIN_X) + (1.0 / aa * n) - 1.0, thr);
			//	thr->WIN_X += 1.0 / aa * n;
				tmp = ft_calc_obj(thr, thr->recursivity);
				argb_mult(&tmp, .5, thr),
				argb_add(&thr->color, tmp, thr);
			}
			//thr->color /= 4;
			n = aa;
		}
		else
		{
			thr->recursivity = thr->e->recursivity;
			ft_calc_ray(i % thr->WIN_X, i / thr->WIN_X, thr);
			thr->color = ft_calc_obj(thr, thr->recursivity);
		}
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
