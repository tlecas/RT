#include "rt.h"

void	ft_black_filter(t_env *e)
{
	int				i;
	unsigned int	tab[3];
	unsigned int	filtbw;
	unsigned int	color;

	i = 0;
	while (i < e->win_area)
	{
		color = e->data[i];
		color <<= 8;
		tab[0] = (color >> 24);
		color <<= 8;
		tab[1] = (color >> 24);
		color <<= 8;
		tab[2] = (color >> 24);
		filtbw = (tab[0] + tab[1] + tab[2]) / 3;
		e->data[i] = (filtbw << 16) + (filtbw << 8) + filtbw;
		++i;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	ft_display_info(e->keys, e);
	mlx_do_sync(e->mlx);
}
