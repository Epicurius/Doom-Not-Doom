/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:40:11 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/24 18:04:37 by nneronin         ###   ########.fr       */
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
		doom->name		= ft_strdup(arr[2]);
		doom->vert		= (t_xyz	*)malloc(sizeof(t_xyz	) * ft_atoi(arr[3]));
		doom->walls		= (t_wall	*)malloc(sizeof(t_wall	) * ft_atoi(arr[4]));
		doom->sectors 	= (t_sector	*)malloc(sizeof(t_sector) * ft_atoi(arr[5]));
		doom->entity 	= (t_entity	*)malloc(sizeof(t_entity) * ft_atoi(arr[6]));
		SECTORNUM		= ft_atoi(arr[5]);
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_wall(t_doom *doom, int fd)
{
	int		id;
	char	*line;
	char	**arr;
	t_wall	*wall;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr				= ft_strsplit(line, '\t');
		wall			= &doom->walls[ft_atoi(arr[0])];
		wall->v1		= doom->vert[ft_atoi(arr[1])];
		wall->v2		= doom->vert[ft_atoi(arr[2])];
		wall->texture	= ft_atoi(arr[3]);
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
		arr				= ft_strsplit(line, '\t');
		PLAYER.where.x	= atof(arr[0]);
		PLAYER.where.y	= atof(arr[1]);
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
		doom->vert[id].x	= atof(arr[1]);
		doom->vert[id].y	= atof(arr[2]);
		doom->vert[id].z	= atof(arr[3]);
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

void	add_sector_points(t_sector *sect, t_wall *walls, char **wall, char **neighbour)
{
	int l;

	l = -1;
	printf("%d\n", sect->npoints);
	while (++l < sect->npoints)
	{
		sect->vertex[l]			= walls[atoi(wall[l])].v1;
		sect->textures[l]		= walls[atoi(wall[l])].texture;
		sect->neighbors[l]		= atoi(neighbour[l]);
	}
	//sect->vertex[0] = sect->vertex[sect->npoints]; // Ensure the vertexes form a loop
	sect->vertex[sect->npoints] = sect->vertex[0]; // Ensure the vertexes form a loop
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
		arr				= ft_strsplit(line, '\t');
		sect			= &doom->sectors[ft_atoi(arr[0])];
		sect->floor		= ft_atoi(arr[1]);
		sect->ceil		= ft_atoi(arr[2]);
		walls			= ft_strsplit(arr[3], ' ');
		sect->npoints   = npoints(walls);
		sect->neighbors = (signed char *)malloc(sizeof(signed char) * (sect->npoints));
		sect->textures	= (signed char *)malloc(sizeof(signed char) * (sect->npoints));
		sect->vertex    = (t_xyz *)malloc(sizeof(t_xyz) * (sect->npoints + 1));
		neighbour		= ft_strsplit(arr[4], ' ');
		sect->gravity	= atof(arr[7]);
		sect->light		= atof(arr[8]);
		sect->entity_nb	= 0;
		add_sector_points(sect, doom->walls, walls, neighbour);
		free_array(arr);
		free_array(walls);
		free_array(neighbour);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

int		find_coord_sector(t_doom *doom, t_xyz p)
{
	int		i;
	int		j;
	int		s;
	t_xyz	*v;

	s = -1;
	while (++s < SECTORNUM)
	{
		i = 0;
		v = doom->sectors[s].vertex;
		j = doom->sectors[s].npoints - 1;
		while (i < doom->sectors[s].npoints)
		{
			if (((v[i].y > p.y) != (v[j].y > p.y)) &&
					(p.x < (v[j].x - v[i].x) * (p.y - v[i].y)
				 	/ (v[j].y - v[i].y) + v[i].x) )
			{
				PLAYER.sector = s;
				PLAYER.where.z = doom->sectors[s].floor + EYE_HEIGHT;
				return (1);
			}
			j = i++;
		}
	}
	return (0);
}

int		find_entity_sector(t_doom *doom, t_xyz e)
{
	int		i;
	int		j;
	int		s;
	t_xyz	*v;

	s = -1;
	while (++s < SECTORNUM)
	{
		i = 0;
		v = doom->sectors[s].vertex;
		j = doom->sectors[s].npoints - 1;
		while (i < doom->sectors[s].npoints)
		{
			if (((v[i].y > e.y) != (v[j].y > e.y)) &&
					(e.x < (v[j].x - v[i].x) * (e.y - v[i].y)
				 	/ (v[j].y - v[i].y) + v[i].x) )
			{
				return (s);
			}
			j = i++;
		}
	}
	return (-1);
}
void	read_entity(t_doom *doom, int fd)
{
	char		*line;
	char		**arr;
	t_entity	entity;
	t_sector	*sect;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr					= ft_strsplit(line, '\t');

		entity.where.x		= atof(arr[1]);
		entity.where.y		= atof(arr[2]);
		entity.where.z		= atof(arr[3]);
		sect				= &doom->sectors[find_entity_sector(doom, entity.where)];
		sect->entity[sect->entity_nb] = entity;
		sect->entity_nb		+= 1;

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
		ft_strdel(&line);
	}
	close(fd);
	free(line);
	if (!find_coord_sector(doom, doom->player.where))
	{
		printf("ERROR: Invalide player spawn.\n");
		return (0);
	}
	return (1);
}
