/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/06/02 10:06:20 nneronin
 * Updated: 2021/12/12 15:29:47 nneronin
 */

#include "doom.h"

float	ceiling_at(t_sector *sector, t_v3 pos)
{
	float	peq;
	t_v3	v;

	v = sector->wall[sector->ceiling_incl_start]->v1;
	peq = sector->top_normal.x * (pos.x - v.x)
		- sector->top_normal.y * (pos.y - v.y);
	return (peq * sector->ceiling_incl_angle + sector->ceiling.height);
}

float	floor_at(t_sector *sector, t_v3 pos)
{
	float	peq;
	t_v3	v;

	v = sector->wall[sector->floor_incl_start]->v1;
	peq = sector->bot_normal.x * (pos.x - v.x)
		- sector->bot_normal.y * (pos.y - v.y);
	return (peq * sector->floor_incl_angle + sector->floor.height);
}

//		normal of 2 vectors will be the slope direction (unit vectort normal)
static t_v2	get_unit_normal_vector(t_sector *sector, int wall)
{
	t_v3	v1;
	t_v3	v2;
	t_v2	normal;
	float	m;

	v1 = sector->wall[wall]->v1;
	v2 = sector->wall[wall]->v2;
	m = point_distance_v2(v1.x, v1.y, v2.x, v2.y);
	normal.x = -((v2.y - v1.y) / m);
	normal.y = -((v2.x - v1.x) / m);
	return (normal);
}

void	init_slope_normal(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		doom->sectors[i].bot_normal = get_unit_normal_vector(&doom->sectors[i],
				doom->sectors[i].floor_incl_start);
		doom->sectors[i].top_normal = get_unit_normal_vector(&doom->sectors[i],
				doom->sectors[i].ceiling_incl_start);
	}
}
