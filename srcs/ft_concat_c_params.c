/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_concat_c_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 09:36:03 by tlecas            #+#    #+#             */
/*   Updated: 2018/04/30 00:28:32 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_mat		ft_mat_init(void)
{
	t_mat mat;

	mat.ambient = 0;
	mat.diffuse = 0;
	mat.specular = 0;
	mat.reflection = 0;
	mat.refraction = 0;
	return (mat);
}

static void	ft_init_params_concat_c_params(int *i, int *j, int *k, int *l)
{
	*j = -1;
	*i = 0;
	*k = 0;
	*l = -1;
}

char		*ft_concat_c_params(char *str1, const char *str2, char c)
{
	char	*ret;
	int		i;
	int		j;
	int		k;
	int		l;

	ft_init_params_concat_c_params(&i, &j, &k, &l);
	if (str1 == 0 && --k)
		i = ft_strlen(str2) + 1;
	else if (str1 != 0 && ++k)
		i = ft_strlen(str1) + ft_strlen(str2) + 1;
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		ft_error("Error malloc!", 0, 0);
	while (++j <= i)
	{
		if (k == 1 && str1[j])
			ret[j] = str1[j];
		else if (k == 1 && str1[j] == '\0' && k--)
			ret[j] = c;
		else if (k <= 0)
			ret[j] = str2[++l];
	}
	if (str1)
		free(str1);
	return (ret);
}
