
#include "doom.h"

//	Returns 1 if collision 0 if not
int	hitbox_collision1(t_xyz dest, t_wall *wall)
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

int	fit_through_portal1(t_doom *doom, t_sector *sector, t_wall *wall, t_entity *entity)
{
	double portal_top;
	double portal_bot;

	portal_bot = max(sector->floor.y, doom->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, doom->sectors[wall->n].ceiling.y);
	if (portal_top > entity->where.z + entity->stat.height &&
		portal_bot <= entity->where.z)
		return (1);
	return (0);
}

void	horizontal_entity_collision(t_doom *doom, t_entity *entity)
{
	int i;
	t_sector *sector;
	t_wall *wall;
	t_xyz	dest;

	i = -1;
	sector = &doom->sectors[entity->sector];
	dest.x = entity->where.x + entity->velocity.x;
	dest.y = entity->where.y + entity->velocity.y;
	while (++i < sector->npoints)
	{
		wall = sector->wall[i];
		if (intersect_check(entity->where, dest, wall->v1, wall->v2))
		{
			if (wall->n == -1)
				return ;
			if (!fit_through_portal1(doom, sector, wall, entity))
				return ;
			if (doom->sectors[wall->n].floor.y < sector->floor.y)
				entity->ground = 0;
			entity->sector = wall->n;
			break ;
		}
		else if ((wall->n == -1 || !fit_through_portal1(doom, sector, wall, entity))
			&& hitbox_collision1(dest, wall))
			return ;
	}
	entity->where.x += entity->velocity.x;
	entity->where.y += entity->velocity.y;
}

void	vertical_entity_collision(t_doom *doom, t_entity *entity)
{
	double	new_z;
	t_sector sector;

	sector = doom->sectors[entity->sector];
	if (!entity->stat.flying)
		entity->velocity.z -= sector.gravity;
	new_z = entity->where.z + entity->velocity.z;
	// So to not keep on falling through floor.
	if (entity->velocity.z < 0 && new_z < sector.floor.y + entity->stat.height)
	{
		entity->where.z = sector.floor.y;
		entity->velocity.z = 0;
		entity->ground = 1;
	}
	// If player has reached the cealing.
	else if (entity->velocity.z > 0 && new_z + 1 > sector.ceiling.y)
		entity->velocity.z = 0;
	// Let the player keep on falling.
	else if (!entity->ground || entity->stat.flying)
		entity->where.z += entity->velocity.z;
}

void	get_entity_movement(t_doom *doom, t_entity *entity)
{
	t_xyz	*v;
	double	dist;
	double	speed;
	double	z;

	v = &entity->velocity;
	z = entity->stat.flying ? 1 : EYE_LVL;
	speed = entity->stat.speed * (SDL_GetTicks() - doom->fps.curr);
	v->x = entity->dest.x - entity->where.x;
	v->y = entity->dest.y - entity->where.y;
	v->z = entity->dest.z - entity->where.z;
	if (v->x == 0 && v->y == 0 && v->z == 0)
		return ;
	dist = space_diagonal(v->x, v->y, v->z);
	v->x *= speed / dist;
	v->y *= speed / dist;
	v->z *= (entity->stat.flying ? speed / dist : 0);
}	
/*
void	ai_movement(t_doom *doom, t_entity *entity)
{
	get_entity_movement(doom, entity);
	vertical_entity_collision(doom, entity);
	horizontal_entity_collision(doom, entity);
	entity->yaw = angle_to_point(entity->where, entity->dest);
}
*/

void	ai_movement(t_doom *doom, t_entity *entity)
{
	t_collision_thread e[1];

	get_entity_movement(doom, entity);
	e->where		= &entity->where;
	e->velocity		= &entity->velocity;
	e->sector		= entity->sector;
	e->sectors		= doom->sectors;
	e->entities		= doom->entity;
	e->nb_entities		= doom->nb.entities;
	e->player		= 0;
	e->hitbox_height	= PLAYER_HEIGHT;
	e->hitbox_radius	= PLAYER_RADIUS;
	e->step_height		= 1;
	tpool_add(&doom->tpool, collision_detection, &e);
	tpool_wait(&doom->tpool);
	entity->yaw = angle_to_point(entity->where, entity->dest);
}
