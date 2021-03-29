
#include "doom.h"

t_xyz	projectile_movement(t_xyz curr, t_xyz dest)
{
	t_xyz	move;
	double	dist;
	double	speed = 0.5;

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
	if (entity->frame + 1 < doom->sprites[entity->type].nb[ATTACK][FRAMES])
		return ;
	if (1 == 2 && doom->sprites[entity->type].nb[DEATH][FRAMES] == 0)
	{
		doom->player.hp -= entity->stat.dmg;
		entity->render = 0;
		printf("Explode\n");
	}
	else if (!entity->orb->render)
	{
		entity->orb->render = 1;
		entity->orb->velocity = projectile_movement(entity->where, doom->player.where);
		entity->orb->where.x = entity->where.x;// + entity->orb->velocity.x;
		entity->orb->where.y = entity->where.y;// + entity->orb->velocity.y;
		entity->orb->where.z = entity->where.z + 4;// + entity->orb->velocity.z;
		entity->orb->sector = entity->sector;
		entity->render = 0;
	}
}
