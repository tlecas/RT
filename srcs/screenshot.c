/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 22:53:28 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 18:59:55 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t	count(int n)
{
	size_t	i;

	if (!n)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		++i;
	}
	return (i);
}

static char		*fname(t_env *e)
{
	time_t	epoch;
	char	*tmp;
	char	*buf;
	char	*f_name;

	time(&epoch);
	!(buf = ft_strdup(e->filename)) ? ft_error("strjoin error", 0, 0) : 0;
	tmp = buf;
	buf = ft_strrchr(buf, '/');
	buf[ft_strrchr(buf, '.') - buf] = '\0';
	if (!(buf = ft_strjoin(buf, "_%d_%m_%Y_%H-%M-%S")))
		ft_error("strjoin error", 0, 0);
	ft_strdel(&tmp);
	!(f_name = ft_strnew(128)) ? ft_error("strjoin error", 0, 0) : 0;
	strftime(f_name, 128, buf, localtime(&epoch));
	ft_strdel(&buf);
	tmp = f_name;
	if (!(f_name = ft_strjoin("./screenshots", f_name)))
		ft_error("strjoin error", 0, 0);
	ft_strdel(&tmp);
	tmp = f_name;
	!(f_name = ft_strjoin(f_name, ".ppm")) ? ft_error("strjoin error", 0, 0) : 0;
	ft_strdel(&tmp);
	return (f_name);
}

static int		header(t_env *e, int fd)
{
	size_t	nbyte;
	char	*header;
	char	*tmp;

	nbyte = 9 + count(WIN_X) + count(WIN_Y);
	header = ft_strdup("P6\n");
	tmp = header;
	header = ft_strjoin(header, ft_itoa(WIN_X));
	ft_strdel(&tmp);
	tmp = header;
	header = ft_strjoin(header, " ");
	ft_strdel(&tmp);
	tmp = header;
	header = ft_strjoin(header, ft_itoa(WIN_Y));
	ft_strdel(&tmp);
	tmp = header;
	header = ft_strjoin(header, "\n255\n");
	ft_strdel(&tmp);
	if (write(fd, header, nbyte) == -1)
	{
		ft_strdel(&header);
		return (-1);
	}
	ft_strdel(&header);
	return (0);
}

void			screenshot(t_env *e)
{
	int		fd;
	int		i;
	char	*name;
	char	*data;

	data = ft_memalloc(900);
	name = fname(e);
	if ((fd = open(name, O_WRONLY | O_CREAT, OFLAGS)) == -1)
		ft_error("open error", 0, 0);
	ft_strdel(&name);
	if (header(e, fd) == -1)
		ft_error("write error", 0, 0);
	i = 0;
	while (i < e->win_area)
	{
		data[(i * 3) % 900] = e->tmpaddr[i * 4 + 2];
		data[(i * 3 + 1) % 900] = e->tmpaddr[i * 4 + 1];
		data[(i * 3 + 2) % 900] = e->tmpaddr[i * 4 + 0];
		if ((i * 3) % 900 == 897)
		{
			ft_putnbr(i * 4 + 2);
			ft_putchar('\n');
			write(fd, &data, 900);
		}

		++i;
	}
	write(fd, &data, (i * 3) % 900);
	//printf("%d\n", e->win_area);
	free(data);
}
