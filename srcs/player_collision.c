
#include "doom.h"

int	vertical_collision3(t_collision_thread *entity, t_xyz dest)
{
	t_sector sector;

	sector = entity->sectors[entity->sector];
	// So to not keep on falling through floor.
	if (entity->velocity->z < 0 && dest.z < sector.floor.y)
	{
		entity->where->z = sector.floor.y;
		return (1);
	}
	// If player has reached the cealing.
	else if (entity->velocity->z > 0 && dest.z + entity->hitbox_height > sector.ceiling.y)
		return (1);
	// Let the player keep on rising/falling.
	else
		entity->where->z += entity->velocity->z;
	return (0);
}

int	hitbox_collision3(t_xyz dest, t_wall *wall, float hitbox_radius)
{
	t_xyz point;

	//Dose player hitbox collide with vetex 1.
	if (point_distance_2d(wall->v1.x, wall->v1.y, dest.x, dest.y) <= hitbox_radius)
		return (1);
	//Dose player hitbox collide with vetex 2.
	if (point_distance_2d(wall->v2.x, wall->v2.y, dest.x, dest.y) <= hitbox_radius)
		return (2);
	point = closest_point_on_segment_2d(dest, wall->v1, wall->v2);
	//Dose player hitbox collide with vertex point closest to the wall.
	if (point_distance_2d(point.x, point.y, dest.x, dest.y) <= hitbox_radius)
		return (3);
	return (0);
}

int	fit_through_portal3(t_collision_thread *entity, t_sector *sector, t_wall *wall)
{
	double portal_top;
	double portal_bot;

	portal_bot = max(sector->floor.y, entity->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, entity->sectors[wall->n].ceiling.y);
	if (portal_top <= portal_bot + entity->hitbox_height)
		return (0);
	if (portal_top > entity->where->z + entity->hitbox_height &&
		portal_bot <= entity->where->z + entity->step_height)
		return (1);
	return (0);
}

int	horizontal_collision3(t_collision_thread *entity, t_xyz dest)
{
	int i;
	t_wall *wall;
	t_sector *sector;

	i = -1;
	sector = &entity->sectors[entity->sector];
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		// Dose path intersecta wall.
		if (intersect_check(*entity->where, dest, wall->v1, wall->v2))
		{
			// Is wall solid.
			if (wall->n == -1)
				return (1);
			// Can fit through portal to next sector.
			if (!fit_through_portal3(entity, sector, wall))
				return (1);
			entity->sector = wall->n;
			break ;
		}
		// Dose hitbox collide with solid surface
		else if ((wall->n == -1 || !fit_through_portal3(entity, sector, wall))
			&& hitbox_collision3(dest, wall, entity->hitbox_radius))
			return (1);
	}
	entity->where->x += entity->velocity->x;
	entity->where->y += entity->velocity->y;
	return (0);
}

int	collision_detection(void *arg)
{
	t_collision_thread *entity;
	t_xyz	dest;

	entity = arg;
	dest = sum_xyz(*entity->where, *entity->velocity);
	if (entity->player && entity_collision(entity, dest))
	{
		entity->velocity->x = 0;
		entity->velocity->y = 0;
		entity->velocity->z = 0;
		return (0);
	}
	if (vertical_collision3(entity, dest))
		entity->velocity->z = 0;
	if (horizontal_collision3(entity, dest))
	{
		entity->velocity->x = 0;
		entity->velocity->y = 0;
	}
	return (0);
}

void	player_collision(t_doom *doom)
{
	t_collision_thread p[1];

	p->where		= &doom->player.where;
	p->velocity		= &doom->player.velocity;
	p->sector		= doom->player.sector;
	p->sectors		= doom->sectors;
	p->entities		= doom->entity;
	p->nb_entities		= doom->nb.entities;
	p->player		= 1;
	p->hitbox_height	= PLAYER_HEIGHT;
	p->hitbox_radius	= PLAYER_RADIUS;
	p->step_height		= STEP_HEIGHT;
	tpool_add(&doom->tpool, collision_detection, &p);
	tpool_wait(&doom->tpool);
}
