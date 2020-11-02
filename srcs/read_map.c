/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 13:40:11 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/02 17:51:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include  <stdio.h>

void	free_array(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
		ft_strdel(&arr[i++]);
	free(arr);
}

void	read_map(t_doom *doom, int fd)
{
	char *line;
	char **arr;
	int	w;
	int h;
	char *name;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = ft_strsplit(line, '\t');
		w = ft_atoi(arr[0]);
		h = ft_atoi(arr[1]);
		name = ft_strdup(arr[2]);
		//doom->vert = (t_xyz *)malloc(sizeof(t_xyz) * ft_atoi(arr[3]));
		doom->walls = (t_wall *)malloc(sizeof(t_wall) * ft_atoi(arr[4]));
		//doom->sectors = (t_sector *)malloc(sizeof(t_sector) * ft_atoi(arr[5]));
		//printf("W:%d, H:%d, Name:%s\n", w, h, name);
		free(name);
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}
void	read_wall(t_doom *doom, int fd)
{
	int id;
	char *line;
	char **arr;
	
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = ft_strsplit(line, '\t');
		id = ft_atoi(arr[0]);
		doom->walls[id].v1 = doom->vert[ft_atoi(arr[1])];
		doom->walls[id].v2 = doom->vert[ft_atoi(arr[2])];
		doom->walls[id].texture = ft_atoi(arr[3]);
		//printf("ID:%d, v1:%f %f %f, v2:%f %f %f, t:%d\n", id, walls[id].v1.x, walls[id].v1.y, walls[id].v1.z,	
		//	walls[id].v2.x,	walls[id].v2.y,	walls[id].v2.z,	walls[id].texture);
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_player(t_doom *doom, int fd)
{
	char *line;
	char **arr;

	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = ft_strsplit(line, '\t');
		PLAYER.where.x = atof(arr[0]);
		PLAYER.where.y = atof(arr[1]);
		PLAYER.velocity = (t_xyz){0, 0, 0};
		PLAYER.angle = 0;
		PLAYER.anglesin = 0;
		PLAYER.anglecos = 0;
		PLAYER.yaw = 0;
		PLAYER.sector = 0;
		PLAYER.where.z = 0 + EYE_HEIGHT; //;doom->sectors[PLAYER.sector].floor + EYE_HEIGHT;
		free_array(arr);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}


void	read_vertex(t_doom *doom, int fd)
{
	char *line;
	char **arr;
	int id;
	int	vertices = 0;

	doom->vert = NULL;
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		arr = ft_strsplit(line, '\t');
		doom->vert = realloc(doom->vert, sizeof(t_xyz) * (vertices + 1));
		doom->vert[vertices].x = atof(arr[1]);
		doom->vert[vertices].y = atof(arr[2]);
		doom->vert[vertices].z = atof(arr[3]);
		free_array(arr);
		//printf("Vert:%d, ID: %d, x:%.2f, y:%.2f, z:%.2f\n", vertices, vertices,
		//				doom->vert[vertices].x,
		//				doom->vert[vertices].y,
		//				doom->vert[vertices].z);
		vertices += 1;
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

void	read_sectors(t_doom *doom, int fd)
{
	t_sector *sect;
	char *line;
	char **arr;
	char **walls;
	char **neighbour;
	
	doom->sectors = NULL;
	while (get_next_line(fd, &line))
	{
		if (line[0] == '-')
			break ;
		doom->sectors = realloc(doom->sectors, ++SECTORNUM * sizeof(t_sector));
		sect = &doom->sectors[SECTORNUM - 1];
		arr = ft_strsplit(line, '\t');
		sect->floor = ft_atoi(arr[0]);
		sect->ceil = ft_atoi(arr[1]);
		walls = ft_strsplit(arr[2], ' ');
		int m = 0;
		while (walls[m] != NULL)
			m++;
		sect->npoints   = m;
		sect->neighbors = (signed char *)malloc(sizeof(signed char) * (m));
		sect->vertex    = (t_xyz *)malloc(sizeof(t_xyz) * (m + 1));
        //for (int l = 0; l < m; ++l)
		//	sect->vertex[l + 1] = doom->vert[atoi(walls[l])];
		//sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop
		
		for (int l = 0; l < m; ++l)
			sect->vertex[l + 1] = doom->walls[atoi(walls[l])].v1;
		sect->vertex[0] = sect->vertex[m]; // Ensure the vertexes form a loop

		neighbour = ft_strsplit(arr[3], ' ');
        for (int l = 0; l < m; ++l)
			sect->neighbors[l] = atoi(neighbour[l]);
		sect->gravity = atof(arr[6]);
		sect->light = atof(arr[7]);
		free_array(arr);
		free_array(walls);
		free_array(neighbour);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

int			read_file(t_doom *doom, char *file_name)
{
	int fd;
	char *line;

	if (!(fd = open(file_name, O_RDONLY)))
			return (-1);
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
		ft_strdel(&line);
	}
	close(fd);
	free(line);
	return (0);
}
