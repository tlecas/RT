#include "rt.h"

void	keys_settings3(int keycode, t_env *e)
{
	if (keycode == KEY_R)
	{
		e->keys ^= ROUGH;
		ft_rt(e);
		ft_check_filters(e);
	}
}
