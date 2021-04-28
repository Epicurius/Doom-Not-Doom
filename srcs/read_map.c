/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:40:11 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/28 10:50:12 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_map_header(t_doom *doom, char **arr)
{
	doom->map_scale		= ft_atof(arr[1]);
	doom->nb.vertices	= ft_atoi(arr[2]);
	doom->nb.walls		= ft_atoi(arr[3]);
	doom->nb.sectors	= ft_atoi(arr[4]);
	doom->nb.entities	= 0;
	doom->vert	= ft_memalloc(sizeof(t_xyz) * doom->nb.vertices);
	doom->walls	= ft_memalloc(sizeof(t_wall) * doom->nb.walls);
	doom->sectors	= ft_memalloc(sizeof(t_sector) * doom->nb.sectors);
}

void	init_map_wall(t_doom *doom, char **arr)
{
	t_wall	*wall;

	wall		= &doom->walls[ft_atoi(arr[0])];
	wall->v1	= doom->vert[ft_atoi(arr[1])];
	wall->v2	= doom->vert[ft_atoi(arr[2])];
	wall->wtx	= ft_atoi(arr[3]);
	wall->ptx	= ft_atoi(arr[4]);
	wall->scale	= ft_atof(arr[5]) * doom->map_scale;
	wall->solid	= ft_atoi(arr[6]);
}

void	init_map_fc(t_doom *doom, char **arr)
{
	int		sect;
	t_plane	*floor;
	t_plane	*ceiling;

	sect			= ft_atoi(arr[1]);
	floor			= &doom->sectors[sect].floor;
	ceiling			= &doom->sectors[sect].ceiling;
	floor->y		= atof(arr[2]) * doom->map_scale;
	ceiling->y		= atof(arr[3]) * doom->map_scale;
	floor->tx		= ft_atoi(arr[4]);
	ceiling->tx		= ft_atoi(arr[5]);
	floor->scale	= atof(arr[6]) * doom->map_scale;
	ceiling->scale	= atof(arr[6]) * doom->map_scale;
}

void	init_map_player(t_doom *doom, char **arr)
{
	t_player *player;

	player		= &doom->player;
	player->where.x	= ft_atof(arr[0]) * doom->map_scale;
	player->where.y	= ft_atof(arr[1]) * doom->map_scale;
	player->where.z	= ft_atof(arr[2]) * doom->map_scale;
	player->yaw	= ft_atoi(arr[3]);
}


void	complete_wall(t_sector *sect, t_wall *walls, char **id, char **neighbour)
{
	int l;
	int wall_nb;

	l = -1;
	while (++l < sect->npoints)
	{
		wall_nb					= ft_atoi(id[l]);
		sect->wall[l]			= &walls[wall_nb];
		sect->wall[l]->id		= wall_nb;
		sect->wall[l]->sect		= sect->id;
		sect->wall[l]->n		= ft_atoi(neighbour[l]);
	}
}

void	init_map_sector(t_doom *doom, char **arr)
{
	t_sector	*sect;
	char		**walls;
	char		**neighbour;

	sect			= &doom->sectors[ft_atoi(arr[0])];
	sect->id		= ft_atoi(arr[0]);
	walls			= ft_strsplit(arr[1], ' ');
	sect->npoints	= ft_strarr_func(walls, NULL);
	sect->wall		= ft_memalloc(sizeof(t_wall*) * (sect->npoints));
	neighbour		= ft_strsplit(arr[2], ' ');
	sect->gravity	= ft_atoi(arr[3]) / 1000.0;
	sect->light		= ft_atoi(arr[4]);
	complete_wall(sect, doom->walls, walls, neighbour);
	ft_strarr_func(walls, ft_strdel);
	ft_strarr_func(neighbour, ft_strdel);
	free(walls);
	free(neighbour);
}

void	init_map_wsprite(t_doom *doom, char **arr)
{
	t_wsprites	*wsprite;
	t_wsprite	*sprite;
	
	wsprite			= &doom->walls[ft_atoi(arr[1])].wsprite;
	wsprite->total 		+= 1;
	wsprite->num 		= ft_realloc(wsprite->num, sizeof(t_wsprite)
						* wsprite->total);
	sprite			= &wsprite->num[wsprite->total - 1];
	sprite->id		= ft_atoi(arr[0]);
	sprite->where.x		= ft_atof(arr[2]) * doom->map_scale;
	sprite->where.y		= ft_atof(arr[3]) * doom->map_scale;
	sprite->scale_w		= ft_atof(arr[4]) * doom->map_scale;
	sprite->tx		= ft_atoi(arr[5]);
}

void	init_map_vertex(t_doom *doom, char **arr)
{
	doom->vert[ft_atoi(arr[0])].x = ft_atof(arr[1]) * doom->map_scale;
	doom->vert[ft_atoi(arr[0])].y = ft_atof(arr[2]) * doom->map_scale;
	doom->vert[ft_atoi(arr[0])].z = ft_atof(arr[3]) * doom->map_scale;
}

void		read_line(t_doom *doom, int fd, void (*f)(t_doom*, char**))
{
	char	*line;
	char	**arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = ft_strsplit(line, '\t');
		f(doom, arr);
		ft_strarr_func(arr, ft_strdel);
		free(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
}

void			read_type(t_doom *doom, int fd, char *line)
{
	if (ft_strnequ(line, "type:map", 8))
		read_line(doom, fd, init_map_header);
	else if (ft_strnequ(line, "type:vertex", 11))
		read_line(doom, fd, init_map_vertex);
	else if (ft_strnequ(line, "type:wall", 8))
		read_line(doom, fd, init_map_wall);
	else if (ft_strnequ(line, "type:spawn", 10))
		read_line(doom, fd, init_map_player);
	else if (ft_strnequ(line, "type:sectors", 12))
		read_line(doom, fd, init_map_sector);
	else if (ft_strnequ(line, "type:entity", 11))
		read_line(doom, fd, init_map_entity);
	else if (ft_strnequ(line, "type:f&c", 8))
		read_line(doom, fd, init_map_fc);
	else if (ft_strnequ(line, "type:wsprite", 12))
		read_line(doom, fd, init_map_wsprite);
}

int			read_file(t_doom *doom, char *file_name)
{
	int fd;
	char *line;

	if (!(fd = open(file_name, O_RDONLY)))
	{
		printf("ERROR: File dose not exist.\n");
		return (0);
	}
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
