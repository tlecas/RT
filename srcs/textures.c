/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:14:07 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/13 17:42:45 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*void				textures(t_env *e)
{
	unsigned char	*textures;
	unsigned int	width;
	unsigned int	height;
	int				x;
	int				y;

	if (lodepng_decode32_file(&textures, &width, &height, "./textures/test.png"))
		printf("texture loading error\n");
	y = 0;
	while (y < WIN_Y)
	{
		x = 0;
		while (x < WIN_X)
		{
			if (x < (int)width && y < (int)height)
			{
				e->data[y * e->sizeline + x * e->bpp / 8] =
					textures[(y * width + x) * 4];
				e->data[y * e->sizeline + x * e->bpp / 8 + 1] =
					textures[(y * width + x) * 4 + 1];
				e->data[y * e->sizeline + x * e->bpp / 8 + 2] =
					textures[(y * width + x) * 4 + 2];
			}
			++x;
		}
		++y;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	free(textures);
}*/
