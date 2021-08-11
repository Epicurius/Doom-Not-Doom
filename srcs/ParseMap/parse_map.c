/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:40:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 16:01:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Parse player pos and yaw.
 */
void	parse_player(t_doom *doom, char **arr)
{
	doom->player.where.x = ft_atof(arr[1]) * doom->map_scale;
	doom->player.where.y = ft_atof(arr[2]) * doom->map_scale;
	doom->player.where.z = ft_atof(arr[3]) * doom->map_scale;
	doom->player.yaw = ft_atoi(arr[4]);
}

/*
 *	Read a line and split it with '\t' and pass the array to function.
 */
void	read_line(t_doom *doom, int fd, void (*f)(t_doom*, char**))
{
	char	*line;
	char	**arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = stringsplit(line, '\t', NULL);
		f(doom, arr);
		free(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
}

/*
 *	Check what type will be read.
 */
static void	read_type(t_doom *doom, int fd, char *line)
{
	if (ft_strnequ(line, "type:map", 8))
		read_line(doom, fd, parse_header);
	else if (ft_strnequ(line, "type:vertex", 11))
		read_line(doom, fd, parse_vertex);
	else if (ft_strnequ(line, "type:wall", 9))
		read_line(doom, fd, parse_wall);
	else if (ft_strnequ(line, "type:spawn", 10))
		read_line(doom, fd, parse_player);
	else if (ft_strnequ(line, "type:sector", 11))
		read_line(doom, fd, parse_sector);
	else if (ft_strnequ(line, "type:entity", 11))
		read_line(doom, fd, parse_entity);
	else if (ft_strnequ(line, "type:f&c", 8))
		read_line(doom, fd, parse_fc);
	else if (ft_strnequ(line, "type:wsprite", 12))
		read_line(doom, fd, parse_wsprite);
	else if (ft_strnequ(line, "type:event", 10))
		read_line(doom, fd, parse_events);
}

/*
 *	Read map and save.
 */
int	parse_map(t_doom *doom, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_msg("File does not exist or could not be opened.\n");
	while (get_next_line(fd, &line))
	{
		read_type(doom, fd, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
	close(fd);
	return (1);
}
