
#include "doom.h"

int	vertical_projectile_collision(t_doom *doom, t_projectile *orb, t_xyz dest)
{
	t_sector sector;

	sector = doom->sectors[orb->sector];
	if (dest.z < sector.floor.y || dest.z > sector.ceiling.y)
		return (1);
	return (0);
}

static int	hitbox_collision(t_xyz dest, t_wall *wall)
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

static int	fit_through_portal(t_doom *doom, t_sector *sector, t_wall *wall, t_xyz where)
{
	double portal_top;
	double portal_bot;

	portal_bot = max(sector->floor.y, doom->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, doom->sectors[wall->n].ceiling.y);
	if (portal_top > where.z && portal_bot <= where.z)
		return (1);
	return (0);
}

int	horizontal_projectile_collision(t_doom *doom, t_projectile *orb, t_xyz dest)
{
	int		i;
	t_wall		*wall;
	t_sector	*sector;

	i = -1;
	sector = &doom->sectors[orb->sector];
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		if (intersect_check(orb->where, dest, wall->v1, wall->v2))
		{
			if (wall->n == -1)
				return (1);
			if (!fit_through_portal(doom, sector, wall, orb->where))
				return (1);
			orb->sector = wall->n;
			break ;
		}
		else if ((wall->n == -1 || !fit_through_portal(doom, sector, wall, orb->where))
			&& hitbox_collision(dest, wall))
			return (1);
	}
	return (0);
}

int	player_contact(t_doom *doom, t_xyz dest)
{
	if (point_distance_3d(doom->player.where, dest) <= 5)
	{
		doom->player.hp -= 200;
		return (1);
	}
	return (0);
}

void	precompute_projectiles(t_doom *doom)
{
	int i;
	t_xyz dest;

	i = -1;
	while (++i < doom->nb.projectiles)
	{
		if (!doom->orb[i].render)
			continue ;
		dest = sum_xyz(doom->orb[i].where, doom->orb[i].velocity);
		if (player_contact(doom, dest))
			doom->orb[i].render = 0;	
		if (vertical_projectile_collision(doom, &doom->orb[i], dest))
			doom->orb[i].render = 0;
		else if (horizontal_projectile_collision(doom, &doom->orb[i], dest))
			doom->orb[i].render = 0;
		else
		{
			doom->orb[i].where.x += doom->orb[i].velocity.x;
			doom->orb[i].where.y += doom->orb[i].velocity.y;
			doom->orb[i].where.z += doom->orb[i].velocity.z;
		}
	}
}
