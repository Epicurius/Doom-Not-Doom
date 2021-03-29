
#include "doom.h"

int	vertical_projectile_collision(t_doom *doom, t_projectile *orb)
{
	double	new_z;
	t_sector sector;

	sector = doom->sectors[orb->sector];
	new_z = orb->where.z + orb->velocity.z;
	if (new_z < sector.floor.y || new_z > sector.ceiling.y)
		return (1);
	return (0);
}

int	hitbox_collision2(t_xyz dest, t_wall *wall)
{
	t_xyz point;

	//Dose player hitbox collide with vetex 1.
	if (point_distance_2d(wall->v1.x, wall->v1.y, dest.x, dest.y) <= PLAYER_RADIUS)
		return (1);
	//Dose player hitbox collide with vetex 2.
	if (point_distance_2d(wall->v2.x, wall->v2.y, dest.x, dest.y) <= PLAYER_RADIUS)
		return (2);
	point = closest_point_on_segment_2d(dest, wall->v1, wall->v2);
	//Dose player hitbox collide with vertex point closest to the wall.
	if (point_distance_2d(point.x, point.y, dest.x, dest.y) <= PLAYER_RADIUS)
		return (3);
	return (0);
}

int	fit_through_portal2(t_doom *doom, t_sector *sector, t_wall *wall, t_xyz where)
{
	double portal_top;
	double portal_bot;

	portal_bot = max(sector->floor.y, doom->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, doom->sectors[wall->n].ceiling.y);
	if (portal_top > where.z && portal_bot <= where.z)
		return (1);
	return (0);
}

int	horizontal_projectile_collision(t_doom *doom, t_projectile *orb)
{
	int i;
	t_sector *sector;
	t_wall *wall;
	t_xyz	dest;

	i = -1;
	sector = &doom->sectors[orb->sector];
	dest.x = orb->where.x + orb->velocity.x;
	dest.y = orb->where.y + orb->velocity.y;
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		if (intersect_check(orb->where, dest, wall->v1, wall->v2))
		{
			if (wall->n == -1)
				return (1);
			if (!fit_through_portal2(doom, sector, wall, orb->where))
				return (1);
			orb->sector = wall->n;
			break ;
		}
		else if ((wall->n == -1 || !fit_through_portal2(doom, sector, wall, orb->where))
			&& hitbox_collision2(dest, wall))
			return (1);
	}
	return (0);
}

void	precompute_projectiles(t_doom *doom)
{
	int i;
	t_xyz move;

	i = -1;
	while (++i < doom->nb.projectiles)
	{
		if (!doom->orb[i].render)
			continue ;
		if (vertical_projectile_collision(doom, &doom->orb[i]))
			doom->orb[i].render = 0;
		else if (horizontal_projectile_collision(doom, &doom->orb[i]))
			doom->orb[i].render = 0;
		else
		{
			doom->orb->where.x += doom->orb->velocity.x;
			doom->orb->where.y += doom->orb->velocity.y;
			doom->orb->where.z += doom->orb->velocity.z;
		}
	}
}
