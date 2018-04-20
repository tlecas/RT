# include "rt.h"

void		ft_display_info(unsigned int keys, t_env *e)
{
	if (keys & AA)
		mlx_string_put(e->mlx, e->win, 10, 10, 0x0000FF00, "ANTIALIASING X2");
	if (keys & ROUGH)
		mlx_string_put(e->mlx, e->win, 10, 30, 0x0000FF00, "ROUGH SURFACE");
	if (keys & BLACK)
		mlx_string_put(e->mlx, e->win, 10, 50, 0x0000FF00, "BLACK FILTER");
	if (keys & FRACTAL)
		mlx_string_put(e->mlx, e->win, 10, 70, 0x0000FF00, "FRACTAL FILTER");
}
