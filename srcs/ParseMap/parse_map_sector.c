/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/04/30 14:20:18 nneronin
 * Updated: 2022/01/18 13:07:45 Niklas Neronin
 */

#include "doom.h"

/*
 *	Parse vertice.
 */
void	parse_vertex(t_doom *doom, int nb, char **arr)
{
	int	i;

	i = ft_atoi(arr[0]);
	if (nb < 3)
		LG_ERROR("Invalid amount of vertex arguments %s\n", arr[0]);
	if (i >= doom->nb.vertices)
		LG_ERROR("Invalid amount of walls.");
	doom->vert[i].x = ft_atoi(arr[1]) * doom->map_scale;
	doom->vert[i].y = ft_atoi(arr[2]) * doom->map_scale;
}

/*
 *	Parse wall.
 */
void	parse_wall(t_doom *doom, int nb, char **arr)
{
	t_wall	*wall;
	int		i;

	i = ft_atoi(arr[0]);
	if (nb < 7)
		LG_ERROR("Invalid amount of wall arguments %s\n", arr[0]);
	if (i >= doom->nb.walls)
		LG_ERROR("Invalid amount of walls.");
	wall = &doom->walls[i];
	wall->v1 = doom->vert[ft_atoi(arr[1])];
	wall->v2 = doom->vert[ft_atoi(arr[2])];
	wall->wtx = ft_atoi(arr[3]);
	wall->ptx = ft_atoi(arr[4]);
	wall->scale_factor = ft_atof(arr[5]) * doom->map_scale;
	wall->solid = ft_atoi(arr[6]);
}

/*
 *	Parse floor and ceiling.
 */
void	parse_fc(t_doom *doom, int nb, char **arr)
{
	t_sector	*sector;
	char		**slope;
	static int	i = 0;

	if (nb < 8)
		LG_ERROR("Invalid amount of f&c arguments %s\n", arr[0]);
	if (i >= doom->nb.sectors)
		LG_ERROR("Invalid amount of f&c.");
	sector = &doom->sectors[i++];
	sector->floor.height = ft_atof(arr[1]) * doom->map_scale;
	sector->ceiling.height = ft_atof(arr[2]) * doom->map_scale;
	sector->floor.tx = ft_atoi(arr[3]);
	sector->ceiling.tx = ft_atoi(arr[4]);
	sector->floor.scale = ft_atof(arr[5]) * doom->map_scale;
	sector->ceiling.scale = ft_atof(arr[6]) * doom->map_scale;
	slope = stringsplit(arr[7], ' ', NULL);
	sector->floor_incl_start = ft_atoi(slope[0]);
	sector->floor_incl_angle = ft_atoi(slope[1]) * CONVERT_TO_RADIANS;
	sector->ceiling_incl_start = ft_atoi(slope[2]);
	sector->ceiling_incl_angle = ft_atoi(slope[3]) * CONVERT_TO_RADIANS;
	free(slope);
}

/*
 *	Link wall to sector walls.
 */
void	complete_wall(t_sector *sect, t_wall *walls,
						char **id, char **neighbour)
{
	int	l;
	int	wall_nb;

	l = -1;
	while (++l < sect->npoints)
	{
		wall_nb = ft_atoi(id[l]);
		sect->wall[l] = &walls[wall_nb];
		sect->wall[l]->id = wall_nb;
		sect->wall[l]->sect = sect->id;
		sect->wall[l]->n = ft_atoi(neighbour[l]);
	}
}

/*
 *	Parse sector.
 */
void	parse_sector(t_doom *doom, int ac, char **arr)
{
	int			nb;
	t_sector	*sector;
	char		**walls;
	char		**neighbour;
	static int	i = 0;

	if (ac < 5)
		LG_ERROR("Invalid amount of sector arguments %s\n", arr[0]);
	if (i >= doom->nb.sectors)
		LG_ERROR("Invalid amount of sectors.");
	sector = &doom->sectors[i++];
	sector->id = ft_atoi(arr[0]);
	walls = stringsplit(arr[1], ' ', &sector->npoints);
	sector->wall = protalloc(sizeof(t_wall *) * (sector->npoints));
	neighbour = stringsplit(arr[2], ' ', &nb);
	sector->gravity = ft_atoi(arr[3]);
	sector->light = ft_clamp(ft_atoi(arr[4]) + 100, 0, 199);
	sector->trigger = FALSE;
	if (nb != sector->npoints)
		LG_ERROR("Sect %d npoints amount.\n", sector->id);
	complete_wall(sector, doom->walls, walls, neighbour);
	free(walls);
	free(neighbour);
}
