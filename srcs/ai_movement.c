
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

int	fit_through_portal1(t_doom *doom, t_sector *sector, t_wall *wall, t_xyz where)
{
	double portal_top;
	double portal_bot;

	portal_bot = max(sector->floor.y, doom->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, doom->sectors[wall->n].ceiling.y);
	if (portal_top > where.z + OVER_HEAD_SPACE &&
		portal_bot <= where.z - EYE_LVL + STEP_HEIGHT)
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
			if (!fit_through_portal1(doom, sector, wall, entity->where))
				return ;
			if (doom->sectors[wall->n].floor.y < sector->floor.y)
				entity->ground = 0;
			entity->sector = wall->n;
			break ;
		}
		else if ((wall->n == -1 || !fit_through_portal1(doom, sector, wall, entity->where))
			&& hitbox_collision1(dest, wall))
			return ;
	}
	entity->where.x += entity->velocity.x;
	entity->where.y += entity->velocity.y;
}

void	vertical_entity_collision(t_doom *doom, t_entity *entity)
{
	double	cam_z = 0;
	double	new_z;
	t_sector sector;

	sector = doom->sectors[entity->sector];
	if (!entity->stat.flying)
		entity->velocity.z -= sector.gravity;
	new_z = entity->where.z + entity->velocity.z;
	// So to not keep on falling through floor.
	if (entity->velocity.z < 0 && new_z < sector.floor.y + cam_z)
	{
		entity->where.z = sector.floor.y + cam_z;
		entity->velocity.z = 0;
		entity->ground = 1;
	}
	// If player has reached the cealing.
	else if (entity->velocity.z > 0 && new_z > sector.ceiling.y)
		entity->velocity.z = 0;
	// Let the player keep on falling.
	else if (!entity->ground || entity->stat.flying)
		entity->where.z += entity->velocity.z;
}

void	get_entity_movement(t_doom *doom, t_entity *entity, t_player player)
{
	t_xyz	*v;
	double	dist;
	double	speed;
	double	z;

	v = &entity->velocity;
	z = entity->stat.flying ? 1 : EYE_LVL;
	speed = entity->stat.speed * (SDL_GetTicks() - doom->fps.curr);
	v->x = player.where.x - entity->where.x;
	v->y = player.where.y - entity->where.y;
	v->z = (player.where.z - z) - entity->where.z;
	if (v->x == 0 && v->y == 0 && v->z == 0)
		return ;
	dist = space_diagonal(v->x, v->y, v->z);
	v->x *= speed / dist;
	v->y *= speed / dist;
	v->z *= (entity->stat.flying ? speed / dist : 0);
}	

void	ai_movement(t_doom *doom, t_entity *entity)
{
	t_player player;

	player = doom->player;
	get_entity_movement(doom, entity, player);
	vertical_entity_collision(doom, entity);
	horizontal_entity_collision(doom, entity);
	entity->yaw = atan2(player.where.y - entity->where.y,
		player.where.x - entity->where.x) * CONVERT_DEGREES;
}
