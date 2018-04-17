#include "rt.h"

void	argb_add(unsigned int *color, unsigned int d, t_thread *thr)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int inv;
	unsigned int filtbw;


	inv = (*color >> 24) + (d >> 24);
	*color <<= 8;
	d <<= 8;
	r = (*color >> 24) + (d >> 24);
	uiclamp(&r, 0, 255);
	*color <<= 8;
	d <<= 8;
	g = (*color >> 24) + (d >> 24);
	uiclamp(&g, 0, 255);
	*color <<= 8;
	d <<= 8;
	b = (*color >> 24) + (d >> 24);
	uiclamp(&b, 0, 255);
	if (thr->keys & BLACK)
	{
		filtbw = (r + g + b) / 3;
		*color = (inv << 24) + (filtbw << 16) + (filtbw << 8) + filtbw;
	}
	else
		*color = (inv << 24) + (r << 16) + (g << 8) + b;
}


void				rgb_mult(unsigned int *color, float f, t_thread *thr)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	inv;

	if ((thr->keys & POP))
		*color *= f;
	else
	{
		inv = (*color >> 24);
		*color <<= 8;
		r = (*color >> 24) * f;
		*color <<= 8;
		g = (*color >> 24) * f;
		*color <<= 8;
		b = (*color >> 24) * f;
		*color = (inv << 24) + (r << 16) + (g << 8) + b;
	}
}
