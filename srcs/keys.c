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
	if (keycode == KEY_A)
	{
		e->keys ^= AA;
		ft_rt(e);
	}
//	if (keycode == KEY_T)
//		textures(e);
	return (1);
}
