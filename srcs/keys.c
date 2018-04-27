# include "rt.h"

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_destroy_window(e->mlx, e->win);
		free(e);
		exit(0);
		return (0);
	}
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
	if (keycode == KEY_UP)
	{
		e->cam->angle.x += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_DOWN)
	{
		e->cam->angle.x -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_LEFT)
	{
		e->cam->angle.y += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_RIGHT)
	{
		e->cam->angle.y -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_A)
	{
		e->cam->angle.z += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_D)
	{
		e->cam->angle.z -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_W)
	{
		e->cam->pos.z += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_S)
	{
		e->cam->pos.z -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_E)
	{
		e->cam->pos.x += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_Q)
	{
		e->cam->pos.x -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_M)
	{
		e->keys ^= BLUR;
		ft_rt(e);
	}
	return (1);
}
