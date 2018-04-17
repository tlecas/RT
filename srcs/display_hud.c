# include "rt.h"

void		ft_display_info(unsigned int keys, t_env *e)
{
	if (keys & BLACK)
		mlx_string_put(e->mlx, e->win, 10, 10, 0x00FFFFFF, "BLACK FILTER");
	if (keys & AA)
		mlx_string_put(e->mlx, e->win, 10, 30, 0x00FFFFFF, "ANTIALIASING X2");
	if (keys & POP)
		mlx_string_put(e->mlx, e->win, 10, 50, 0x00FFFFFF, "POP FILTER");
}
