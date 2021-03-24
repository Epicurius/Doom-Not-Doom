
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

	double eye_height = 2;
	portal_bot = max(sector->floor.y, doom->sectors[wall->n].floor.y);
	portal_top = min(sector->ceiling.y, doom->sectors[wall->n].ceiling.y);
	if (portal_top > where.z + OVER_HEAD_SPACE &&
		portal_bot <= where.z - eye_height + STEP_HEIGHT)
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
	double	cam_z;
	double	new_z;
	t_sector sector;

	entity->flying = 1;
	sector = doom->sectors[entity->sector];
	if (!entity->flying)
		entity->velocity.z -= sector.gravity;
	new_z = entity->where.z + entity->velocity.z;
	cam_z = 2;//player->ducking ? DUCK_HEIGHT : EYE_HEIGHT;
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
	else if (!entity->ground || entity->flying)
		entity->where.z += entity->velocity.z;
}

t_xyz	get_entity_movement(t_doom *doom, t_entity *entity, t_player player)
{
	Uint32	time;
	t_xyz	move;
	double	dist;
	double speed = 0.2;

	//time = SDL_GetTicks() - doom->fps.curr;
	//printf("%u\n", time);
	speed *= 1;//time / 3;
	move.x = player.where.x - entity->where.x;
	move.y = player.where.y - entity->where.y;
	move.z = (player.where.z - 1) - entity->where.z;
	if (move.x == 0 && move.y == 0 && move.z == 0)
		return (move);
	dist = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
	move.x *= speed / dist;
	move.y *= speed / dist;
	move.z *= speed / dist;
	//printf("%f %f\n", entity->where.x, entity->where.y);
	//printf("%f %f\n", move.x, move.y);
	return (move);
}	

void	melee_ai(t_doom *doom, t_entity *entity)
{
	t_xyz move;

	t_player player = doom->player;

	//if (point_distance_2d(entity->where.x, entity->where.y,
	//			player.where.x, player.where.y) <= 5)
	//{
	//	return ;
	//}
	entity->velocity = get_entity_movement(doom, entity, player);
	//printf("%f %f\n", entity->velocity.x, entity->velocity.y);
	vertical_entity_collision(doom, entity);
	horizontal_entity_collision(doom, entity);
	entity->yaw = atan2(player.where.y - entity->where.y,
		player.where.x - entity->where.x) * CONVERT_DEGREES; // - 180
}
