# include "rt.h"

int			key_hook(int keycode, t_env *e)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(e->mlx, e->img);
		mlx_destroy_window(e->mlx, e->win);
		exit(0);
		return (0);
	}
	if (keycode == KEY_B)
	{
		e->keys ^= 0x00000001;
		ft_rt(e);
	}
	if (keycode == KEY_P)
	{
		e->keys ^= 0x00000002;
		ft_rt(e);
	}
	return (1);
}
