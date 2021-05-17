/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:40:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/17 18:36:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	parse_player(t_doom *doom, char **arr)
{
	t_player	*player;

	player = &doom->player;
	player->where.x = ft_atof(arr[0]) * doom->map_scale;
	player->where.y = ft_atof(arr[1]) * doom->map_scale;
	player->where.z = ft_atof(arr[2]) * doom->map_scale;
	player->yaw = ft_atoi(arr[3]);
}

void	read_line(t_doom *doom, int fd, void (*f)(t_doom*, char**))
{
	char	*line;
	char	**arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = ft_strsplit(line, '\t', NULL);
		f(doom, arr);
		free(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
}

void	read_type(t_doom *doom, int fd, char *line)
{
	if (ft_strnequ(line, "type:map", 8))
		read_line(doom, fd, parse_header);
	else if (ft_strnequ(line, "type:vertex", 11))
		read_line(doom, fd, parse_vertex);
	else if (ft_strnequ(line, "type:wall", 8))
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
}

int	read_file(t_doom *doom, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		error_term(doom, "File does not exist.\n");
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
