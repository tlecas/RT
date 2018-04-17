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
	if (keycode == KEY_B)
	{
		e->keys ^= BLACK;
		ft_rt(e);
	}
	if (keycode == KEY_P)
	{
		e->keys ^= POP;
		ft_rt(e);
	}
	if (keycode == KEY_Z)
	{
		e->keys ^= AA;
		ft_rt(e);
	}
//	if (keycode == KEY_T)
//		textures(e);
	if (keycode == KEY_UP)
	{
		e->camera->angle.x += 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_DOWN)
	{
		e->camera->angle.x -= 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_LEFT)
	{
		e->camera->angle.y += 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_RIGHT)
	{
		e->camera->angle.y -= 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_A)
	{
		e->camera->angle.z += 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_D)
	{
		e->camera->angle.z -= 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_W)
	{
		e->camera->pos.z += 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_S)
	{
		e->camera->pos.z -= 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_Q)
	{
		e->camera->pos.x += 4.0f;
		ft_rt(e);
	}
	if (keycode == KEY_E)
	{
		e->camera->pos.x -= 4.0f;
		ft_rt(e);
	}
	return (1);
}
