
#include "doom.h"

t_xyz	projectile_movement(t_xyz curr, t_xyz dest)
{
	t_xyz	move;
	double	dist;
	double	speed = 1;

	move.x = dest.x - curr.x;
	move.y = dest.y - curr.y;
	move.z = dest.z - EYE_LVL - curr.z;
	if (move.x == 0 && move.y == 0 && move.z == 0)
		return (move);
	dist = sqrt(move.x * move.x + move.y * move.y + move.z * move.z);
	move.x *= speed / dist;
	move.y *= speed / dist;
	move.z *= speed / dist;
	return (move);
}

void	ai_attack(t_doom *doom, t_entity *entity)
{
	entity->yaw = angle_to_point(entity->where, doom->player.where);
	if (entity->frame < doom->sprites[entity->type].nb[ATTACK][FRAMES] - 1)
		return ;
	if (doom->sprites[entity->type].nb[DEATH][FRAMES] == 0)
	{
		doom->player.hp -= entity->stat.dmg;
		entity->render = 0;
	}
	else if (!entity->orb->render)
	{
		entity->orb->render = 1;
		entity->orb->velocity = projectile_movement(entity->where, doom->player.where);
		entity->orb->where.x = entity->where.x;
		entity->orb->where.y = entity->where.y;
		entity->orb->where.z = entity->where.z + entity->stat.height / 2;
		entity->orb->sector = entity->sector;
	}
}
