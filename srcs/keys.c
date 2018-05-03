/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 04:57:51 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 20:45:58 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		keys_escape(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_destroy_window(e->mlx, e->win);
		free(e);
		exit(0);
	}
	if (keycode == KEY_N)
	{
		if (!(e->screenshot))
			screenshot(e);
		e->screenshot = 1;
	}
}

static void		keys_texture1(int keycode, t_env *e)
{
	if (keycode == KEY_PAD_SUB)
	{
		e->t_ratio *= 1.25f;
		ft_rt(e);
	}
	if (keycode == KEY_PAD_ADD)
	{
		e->t_ratio *= 0.8f;
		ft_rt(e);
	}
	if (keycode == KEY_PAD_DIVIDE)
	{
		e->c_ratio *= 1.25f;
		ft_rt(e);
	}
	if (keycode == KEY_PAD_MULTIPLY)
	{
		e->c_ratio *= 0.8f;
		ft_rt(e);
	}
}

static void		keys_texture2(int keycode, t_env *e)
{
	if (keycode == KEY_J)
	{
		e->t_x -= 50.0f;
		ft_rt(e);
		ft_check_filters(e);
	}
	if (keycode == KEY_L)
	{
		e->t_x += 50.0f;
		ft_rt(e);
		ft_check_filters(e);
	}
	if (keycode == KEY_I)
	{
		e->t_y += 50.0f;
		ft_rt(e);
		ft_check_filters(e);
	}
	if (keycode == KEY_K)
	{
		e->t_y -= 50.0f;
		ft_rt(e);
		ft_check_filters(e);
	}
}

static void		keys_settings(int keycode, t_env *e)
{
	if (keycode == KEY_B)
	{
		e->keys ^= BLACK;
		if (e->keys & BLACK)
			ft_check_filters(e);
		else
			ft_rt(e);
	}
	if (keycode == KEY_F)
	{
		e->keys ^= FRACTAL;
		ft_rt(e);
		ft_check_filters(e);
	}
	if (keycode == KEY_Z)
	{
		e->keys ^= AA;
		ft_rt(e);
		ft_check_filters(e);
	}
	if (keycode == KEY_R)
	{
		e->keys ^= ROUGH;
		ft_rt(e);
		ft_check_filters(e);
	}
}

int				key_hook(int keycode, t_env *e)
{
	keys_escape(keycode, e);
	keys_texture1(keycode, e);
	keys_texture2(keycode, e);
	keys_settings(keycode, e);
	keys_settings2(keycode, e);
	keys_angle1(keycode, e);
	keys_angle2(keycode, e);
	keys_move1(keycode, e);
	keys_move2(keycode, e);
	return (1);
}
