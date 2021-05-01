
#include "doom.h"

t_xyz	projectile_movement(t_doom *doom, t_xyz curr, t_xyz dest)
{
	t_xyz	move;
	double	dist;
	double	speed = 0.3;

	speed *= SDL_GetTicks() - doom->time.curr;
	move.x = dest.x - curr.x;
	move.y = dest.y - curr.y;
	move.z = dest.z - curr.z;
	if (move.x == 0 && move.y == 0 && move.z == 0)
		return (move);
	dist = space_diagonal(move.x, move.y, move.z);
	move.x *= speed / dist;
	move.y *= speed / dist;
	move.z *= speed / dist;
	return (move);
}

void	ai_attack(t_doom *doom, t_sprite *entity)
{
	t_projectile	*orb;

	entity->yaw = angle_to_point(entity->where, doom->player.where);
	if (entity->frame < doom->sheet[entity->type].nb[ATTACK][FRAMES] - 1)
		return ;
	if (entity->data->attack_style == 2)
		entity->render = 0;
	else if (entity->data->attack_style == 1 && doom->orb == NULL)
	{
		orb = malloc(sizeof(t_projectile));
		orb->velocity = projectile_movement(doom, entity->where, doom->player.where);
		orb->where.x = entity->where.x;
		orb->where.y = entity->where.y;
		orb->where.z = entity->where.z;
		orb->start = orb->where;
		orb->sector = entity->sector;
		ft_lstadd_new(&doom->orb, orb, sizeof(orb));
		doom->nb.projectiles += 1;
	}
}
