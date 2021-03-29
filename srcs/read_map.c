/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:40:11 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 14:16:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include  <stdio.h>

void	free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
		ft_strdel(&arr[i++]);
	free(arr);
}

void	read_map(t_doom *doom, int fd)
{
	char	*line;
	char	**arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr				= ft_strsplit(line, '\t');
		//doom->name			= ft_strdup(arr[0]);
		doom->map_scale			= atof(arr[1]);
		doom->nb.vertices		= ft_atoi(arr[2]);
		doom->nb.walls			= ft_atoi(arr[3]);
		doom->nb.sectors		= ft_atoi(arr[4]);
		doom->nb.entities		= ft_atoi(arr[5]);
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	doom->vert	= ft_memalloc(sizeof(t_xyz) * doom->nb.vertices);
	doom->walls	= ft_memalloc(sizeof(t_wall) * doom->nb.walls);
	doom->sectors	= ft_memalloc(sizeof(t_sector) * doom->nb.sectors);
	doom->floors	= ft_memalloc(sizeof(t_plane) * doom->nb.sectors);
	doom->ceilings	= ft_memalloc(sizeof(t_plane) * doom->nb.sectors);
	doom->entity 	= ft_memalloc(sizeof(t_entity) * doom->nb.entities);
}

void	read_wall(t_doom *doom, int fd)
{
	char	*line;
	char	**arr;
	t_wall	*wall;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr			= ft_strsplit(line, '\t');
		wall			= &doom->walls[ft_atoi(arr[0])];
		wall->v1		= doom->vert[ft_atoi(arr[1])];
		wall->v2		= doom->vert[ft_atoi(arr[2])];
		wall->wtx		= ft_atoi(arr[3]);
		wall->ptx		= ft_atoi(arr[4]);
		wall->scale		= atof(arr[5]) * doom->map_scale;
		wall->solid		= ft_atoi(arr[6]);
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_floor_and_ceiling(t_doom *doom, int fd)
{
	char	*line;
	char	**arr;
	t_plane	*floor;
	t_plane	*ceiling;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr			= ft_strsplit(line, '\t');
		floor			= &doom->floors[ft_atoi(arr[0])];
		ceiling			= &doom->ceilings[ft_atoi(arr[0])];
		floor->y		= atof(arr[1]) * doom->map_scale;
		ceiling->y		= atof(arr[2]) * doom->map_scale;
		floor->tx		= ft_atoi(arr[3]);
		ceiling->tx		= ft_atoi(arr[4]);
		floor->scale		= atof(arr[5]) * doom->map_scale;
		ceiling->scale		= atof(arr[5]) * doom->map_scale;
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_player(t_doom *doom, int fd)
{
	char	*line;
	char	**arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr		= ft_strsplit(line, '\t');
		PLAYER.where.x	= atof(arr[0]) * doom->map_scale;
		PLAYER.where.y	= atof(arr[1]) * doom->map_scale;
		PLAYER.where.z	= atof(arr[2]) * doom->map_scale;
		PLAYER.yaw	= ft_atoi(arr[3]);
		PLAYER.size	= PLAYER_RADIUS;
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}


void	read_vertex(t_doom *doom, int fd)
{
	int		id;
	char	*line;
	char	**arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr					= ft_strsplit(line, '\t');
		id					= ft_atoi(arr[0]);
		doom->vert[id].x	= atof(arr[1]) * doom->map_scale;
		doom->vert[id].y	= atof(arr[2]) * doom->map_scale;
		//doom->vert[id].z	= atof(arr[3]) * doom->map_scale;
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

int		npoints(char **arr)
{
	int n;

	n = 0;
	while (arr[n] != NULL)
		n++;
	return (n);
}

void	complete_wall(t_sector *sect, t_wall *walls, char **id, char **neighbour)
{
	int l;
	int wall_nb;

	l = -1;
	while (++l < sect->npoints)
	{
		wall_nb				= atoi(id[l]);
		sect->wall[l]			= &walls[wall_nb];
		sect->wall[l]->id		= wall_nb;
		sect->wall[l]->sect		= sect->id;
		sect->wall[l]->n		= atoi(neighbour[l]);
	}
}

void	read_sectors(t_doom *doom, int fd)
{
	t_sector	*sect;
	char		*line;
	char		**arr;
	char		**walls;
	char		**neighbour;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr			= ft_strsplit(line, '\t');
		sect			= &doom->sectors[ft_atoi(arr[0])];
		sect->id		= ft_atoi(arr[0]);
		sect->floor		= doom->floors[ft_atoi(arr[1])];
		sect->ceiling		= doom->ceilings[ft_atoi(arr[1])];
		walls			= ft_strsplit(arr[2], ' ');
		sect->npoints		= npoints(walls);
		sect->wall		= ft_memalloc(sizeof(t_wall*) * (sect->npoints));
		neighbour		= ft_strsplit(arr[3], ' ');
		sect->gravity		= atof(arr[4]);
		sect->light		= atoi(arr[5]);
		complete_wall(sect, doom->walls, walls, neighbour);
		free_array(arr);
		free_array(walls);
		free_array(neighbour);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_entity(t_doom *doom, int fd)
{
	char		*line;
	char		**arr;
	t_entity	*entity;
	
	entity = doom->entity;
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr					= ft_strsplit(line, '\t');
		entity->id		= atoi(arr[0]);
		entity->spawn.x		= atof(arr[1]) * doom->map_scale;
		entity->spawn.y		= atof(arr[2]) * doom->map_scale;
		entity->spawn.z		= atof(arr[3]) * doom->map_scale;
		entity->where		= entity->spawn;
		entity->type		= atoi(arr[4]);
		entity->scale		= atoi(arr[5]) * doom->map_scale;
		entity->yaw		= atoi(arr[6]);
		entity->sector		= find_sector(doom, entity->where);
		entity->render		= 1;
		entity++;
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_wsprite(t_doom *doom, int fd)
{
	int		i;
	char		*line;
	char		**arr;
	t_wsprite	*wsprite;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr				= ft_strsplit(line, '\t');
		wsprite				= &doom->walls[ft_atoi(arr[1])].wsprite;
		i				= wsprite->total;
		wsprite->num 			= ft_realloc(wsprite->num,
							sizeof(t_sprite) * (i + 1));
		wsprite->num[i].id		= ft_atoi(arr[0]);
		wsprite->num[i].where.x		= atof(arr[2]) * doom->map_scale;
		wsprite->num[i].where.y		= atof(arr[3]) * doom->map_scale;
		wsprite->num[i].tx		= ft_atoi(arr[4]);
		//wsprite->num[i].refresh	= ft_atoi(arr[5]);
		wsprite->num[i].scale_w		= atof(arr[6]) * doom->map_scale;
		wsprite->total 			+= 1;
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
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
		if (!(ft_strncmp(line, "type:map", 7)))
			read_map(doom, fd);
		else if (!(ft_strncmp(line, "type:vertex", 7)))
			read_vertex(doom, fd);
		else if (!(ft_strncmp(line, "type:wall", 7)))
			read_wall(doom, fd);
		else if (!(ft_strncmp(line, "type:spawn", 10)))
			read_player(doom, fd);
		else if (!(ft_strncmp(line, "type:sectors", 7)))
			read_sectors(doom, fd);
		else if (!(ft_strncmp(line, "type:entity", 7)))
			read_entity(doom, fd);
		else if (!(ft_strncmp(line, "type:f&c", 7)))
			read_floor_and_ceiling(doom, fd);
		else if (!(ft_strncmp(line, "type:wsprite", 7)))
			read_wsprite(doom, fd);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	free(line);
	close(fd);
	PLAYER.sector = find_sector(doom, doom->player.where);
	if (PLAYER.sector == -1)
	{
		printf("ERROR: Invalide player spawn.\n");
		return (0);
	}
	PLAYER.where.z += EYE_LVL;
	return (1);
}
