
#include "doom.h"

void	get_entity_movement(t_doom *doom, t_entity *entity)
{
	t_xyz	*v;
	double	dist;
	double	speed;

	v = &entity->velocity;
	entity->dest.z += entity->stat.flying ? EYE_LVL - 1 : 0;
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

void	ai_movement(t_doom *doom, t_entity *entity)
{
	t_collision_thread e[1];

	get_entity_movement(doom, entity);
	e->where		= &entity->where;
	e->velocity		= &entity->velocity;
	e->sector		= &entity->sector;
	e->sectors		= doom->sectors;
	e->entities		= doom->entity;
	e->nb_entities		= doom->nb.entities;
	e->player		= 0;
	e->hitbox_height	= PLAYER_HEIGHT;
	e->hitbox_radius	= 5;
	e->step_height		= 1;
	collision_detection(&e);
	//tpool_add(&doom->tpool, collision_detection, &e);
	//if(!tpool_wait(&doom->tpool))
	//	ft_printf("tpool error\n");
	entity->yaw = angle_to_point(entity->where, entity->dest);
	//printf("%d in sector %d\n", entity->id, entity->sector);
}
