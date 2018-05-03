#include "rt.h"

void	ft_check_filters(t_env *e)
{
	if (e->keys & CARTOON)
		{
			ft_cartoon_filter(e);
			mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
			ft_display_info(e->keys, e);
		}
	if (e->keys & BLACK)
			ft_black_filter(e);
	if (e->keys & SEPIA)
			ft_sepia_filter(e);
}
