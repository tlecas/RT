#include "rt.h"

void		keys_angle1(int keycode, t_env *e)
{
	if (keycode == KEY_DOWN)
	{
		e->cam->angle.x += 4.0f;
		if (e->keys & BLUR)
			e->blur = 3;
		ft_rt(e);
	}
	if (keycode == KEY_UP)
	{
		e->cam->angle.x -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 3;
		ft_rt(e);
	}
	if (keycode == KEY_RIGHT)
	{
		e->cam->angle.y += 4.0f;
		if (e->keys & BLUR)
			e->blur = 2;
		ft_rt(e);
	}
}

void		keys_angle2(int keycode, t_env *e)
{
	if (keycode == KEY_LEFT)
	{
		e->cam->angle.y -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 2;
		ft_rt(e);
	}
	if (keycode == KEY_Q)
	{
		e->cam->angle.z += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_E)
	{
		e->cam->angle.z -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
}

void		keys_move1(int keycode, t_env *e)
{
	if (keycode == KEY_W)
	{
		e->cam->pos.y += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_S)
	{
		e->cam->pos.y -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_2)
	{
		e->cam->pos.z += 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
}

void		keys_move2(int keycode, t_env *e)
{
	if (keycode == KEY_3)
	{
		e->cam->pos.z -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 1;
		ft_rt(e);
	}
	if (keycode == KEY_D)
	{
		e->cam->pos.x += 4.0f;
		if (e->keys & BLUR)
			e->blur = 2;
		ft_rt(e);
	}
	if (keycode == KEY_A)
	{
		e->cam->pos.x -= 4.0f;
		if (e->keys & BLUR)
			e->blur = 2;
		ft_rt(e);
	}
}

void		keys_blur(int keycode, t_env *e)
{
	if (keycode == KEY_M)
	{
		e->keys ^= BLUR;
		ft_rt(e);
	}
}
