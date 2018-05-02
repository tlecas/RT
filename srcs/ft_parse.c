/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlecas <tlecas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:50:12 by tlecas            #+#    #+#             */
/*   Updated: 2018/05/02 15:16:05 by tlecas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			ft_read_file(t_env *e, char *line)
{
	if (line && line[0] != '\t' && ft_strcmp(line, "camera:"))
	{
		if (!ft_strcmp(line, "sphere:"))
			e->objnb->sphere++;
		else if (!ft_strcmp(line, "cylinder:"))
			e->objnb->cylinder++;
		else if (!ft_strcmp(line, "cone:"))
			e->objnb->cone++;
		else if (!ft_strcmp(line, "plane:"))
			e->objnb->plane++;
		else if (!ft_strcmp(line, "paraboloid:"))
			e->objnb->para++;
		else if (!ft_strcmp(line, "light:"))
			e->objnb->light++;
		else
			return (-1);
	}
	e->objnb->totobj = e->objnb->sphere + e->objnb->cylinder + e->objnb->cone +
		e->objnb->plane + e->objnb->light + e->objnb->para;
	return (1);
}

char		**ft_parse_file(t_env *e)
{
	char	*line;
	int		i;
	char	*str;
	char	**tab;

	i = -1;
	str = 0;
	if ((e->fd = open(e->filename, O_RDONLY)) == -1)
		ft_error("The file does not exist!", 0, 0);
	while (get_next_line(e->fd, &line))
	{
		if (++i <= 4 && ft_parse_main_properties(e, line) == -1)
			ft_error("error parse main properties.", 0, 0);
		if (i > 4 && ft_read_file(e, line) == -1)
			ft_error("error parsing object properties.", 0, 0);
		str = ft_concat_c_params(str, line, '\n');
		free(line);
	}
	if (str == 0)
		ft_error("Empty file.", 0, 0);
	tab = ft_strsplit(str, '\n');
	free(str);
	free(line);
	close(e->fd);
	return (tab);
}
