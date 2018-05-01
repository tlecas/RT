/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/03 14:52:38 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 06:13:19 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int ft_calc_obj(t_thread *thr, int recursivity)
{
	float	obj[thr->e->objnb->totobj];
	int		i;
	int		x;

	x = 0;
	i = 0;
	thr->recursivity = recursivity;
	while (thr->e->objnb->sphere != 0 && i < thr->e->objnb->sphere)
	{
		obj[i] = ft_calc_sphere(thr->e->sphere[i], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	while (thr->e->objnb->plane != 0 && (x) < thr->e->objnb->plane)
	{
		obj[i] = ft_calc_plan(thr->e->plane[x], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	while (thr->e->objnb->cylinder != 0 && (x) < thr->e->objnb->cylinder)
	{
		obj[i] = ft_calc_cylinder(thr->e->cylinder[x], &thr->ray);
		i++;
		++x;
	}
	x = 0;
	while (thr->e->objnb->cone != 0 && (x) < thr->e->objnb->cone)
	{
		obj[i] = ft_calc_cone(thr->e->cone[x], &thr->ray);
		i++;
		++x;
	}
	i = ft_isview(obj, i - 1);
	return (ft_load_post(thr, i, obj[i]));
}

static void ft_calc_ray(float x, float y, t_thread *thr)
{
	x = (2.0f * (x + 0.5f) / thr->WIN_X - 1.0f) * tanf(thr->e->fov * 0.5f * M_PI / 180.0f);
	y = (1.0f - 2.0f * ((y + 0.5f) / thr->WIN_Y)) * tanf(thr->e->fov * 0.5f * M_PI / 180.0f);
	x = x * thr->WIN_X / thr->WIN_Y;
	thr->ray.dir = vrotate(normalize(coord_v (x, y, 1)), thr->e->cam->angle);
	thr->ray.pos = thr->e->cam->pos;
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
	aa = (thr->keys & AA);
	n = aa;
	while (i < thr->e->win_area)
	{
		thr->color = 0x00000000;
		if (aa && !(thr->e->blur))
		{
			while (n-- > 0)
			{
				thr->recursivity = thr->e->recursivity;
				ft_calc_ray((i % thr->WIN_X) + (1.0f / aa * n), (i / thr->WIN_X) + (1.0f / aa * n), thr);
				tmp = ft_calc_obj(thr, thr->recursivity);
				rgb_mult(&tmp, 0.5f, thr),
				rgb_add(&thr->color, tmp, thr);
			}
			n = aa;
		}
		else
		{
			thr->recursivity = thr->e->recursivity;
			if ((thr->e->keys & BLUR) && thr->e->blur == 3)
				ft_calc_ray(i % (thr->WIN_X), i / (thr->WIN_X) + ((rand() % 32) / 8) - 2, thr);
			else if ((thr->e->keys & BLUR) && thr->e->blur == 2)
				ft_calc_ray(i % (thr->WIN_X) + ((rand() % 32) / 8) - 2, i / (thr->WIN_X), thr);
			else if ((thr->e->keys & BLUR) && thr->e->blur)
				ft_calc_ray(i % (thr->WIN_X) + ((rand() % 32) / 8) - 2, i / (thr->WIN_X) + ((rand() % 32) / 8) - 2, thr);
			else
				ft_calc_ray(i % (thr->WIN_X), i / (thr->WIN_X), thr);
			thr->color = ft_calc_obj(thr, thr->recursivity);
		}
		thr->e->data[i] = thr->color;
		i += THREADS;
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
	ft_display_info(e->keys, e);
	if ((e->keys & BLUR) && e->blur)
	{
		mlx_do_sync(e->mlx);
		e->blur = 0;
		ft_rt(e);
	}
}
