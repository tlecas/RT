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
	if (keycode == KEY_I)
	{
		e->t_y -= 50.0f;
		ft_rt(e);
	}
	if (keycode == KEY_K)
	{
		e->t_y += 50.0f;
		ft_rt(e);
	}
}

static void		keys_texture2(int keycode, t_env *e)
{
	if (keycode == KEY_J)
	{
		e->t_x -= 50.0f;
		ft_rt(e);
	}
	if (keycode == KEY_L)
	{
		e->t_x += 50.0f;
		ft_rt(e);
	}
}

static void		keys_settings(int keycode, t_env *e)
{
	if (keycode == KEY_B)
	{
		e->keys ^= BLACK;
		ft_rt(e);
	}
	if (keycode == KEY_F)
	{
		e->keys ^= FRACTAL;
		ft_rt(e);
	}
	if (keycode == KEY_Z)
	{
		e->keys ^= AA;
		ft_rt(e);
	}
	if (keycode == KEY_R)
	{
		e->keys ^= ROUGH;
		ft_rt(e);
	}
}

int				key_hook(int keycode, t_env *e)
{
	keys_escape(keycode, e);
	keys_texture1(keycode, e);
	keys_texture2(keycode, e);
	keys_settings(keycode, e);
	keys_angle1(keycode, e);
	keys_angle2(keycode, e);
	keys_move1(keycode, e);
	keys_move2(keycode, e);
	keys_blur(keycode, e);
	return (1);
}
