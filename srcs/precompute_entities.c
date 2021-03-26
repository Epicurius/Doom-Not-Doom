
#include "doom.h"

void	frame_animation(t_doom *doom, t_entity *entity)
{
	if (entity->time - doom->fps.curr < -(entity->stat.frame_rate[entity->state]))
	{
		entity->frame++;
		entity->time = doom->fps.curr;
	}
	if (entity->frame >= doom->sprites[entity->tx].nb[entity->state][FRAMES])
		entity->frame = 0;
		
}

void	entity_fov(t_doom *doom, t_entity *entity)
{
	double left;
	double right;

	left = entity->yaw + 65;
	right = entity->yaw - 65;
	if (left > 360)
		left -= 360;
	if (right < 0)
		right += 360;
	left = (left * CONVERT_RADIANS);
	right = (right * CONVERT_RADIANS);
	entity->far_left.x = 1000 * cos(left) + entity->where.x;
	entity->far_left.y = 1000 * sin(left) + entity->where.y;
	entity->far_right.x = 1000 * cos(right) + entity->where.x;
	entity->far_right.y = 1000 * sin(right) + entity->where.y;
}

int	entity_see(t_doom *doom, t_entity *entity, double dist)
{
	int l;
	int r;

	l = point_side(entity->far_left, entity->where, doom->player.where);
	r = point_side(entity->where, entity->far_right, doom->player.where);
	if (l > 0 && r > 0)
		return (1);
	return (0);
}

int	entity_line_of_sight(t_doom *doom, t_entity *entity, double dist)
{
	entity_fov(doom, entity);
	if (dist < entity->stat.detection_radius)
		return (1);
	if (entity_see(doom, entity, dist))
		return (2);
	return (0);
}

void	get_entity_state(t_doom *doom, t_entity *entity)
{
	double dist;
	int prev_state;

	if (entity->state == DEATH)
		return ;
	dist = point_distance_2d(entity->where.x, entity->where.y,
			doom->player.where.x, doom->player.where.y);
	prev_state = entity->state;
	if (entity->stat.view_distance + 10 < dist)
		entity->state = IDLE;
	else if (entity->stat.attack_range > dist)
		entity->state = ATTACK;
	else if (entity_line_of_sight(doom, entity, dist))
		entity->state = MOVE;
	else if (entity->stat.hp < 0)
		entity->state = DEATH;
	if (entity->state != prev_state)
		entity->frame = 0;

}

void	preforme_entiy_state_fuction(t_doom *doom, t_entity *entity)
{
	if (entity->state == MOVE)
		ai_movement(doom, entity);
	else if (entity->state == ATTACK)
		ai_attack(doom, entity);
			
}

void	get_coresponding_entity_state_frame(t_doom *doom, t_entity *entity)
{
	if (doom->sprites[entity->tx].nb[entity->state][FRAMES] > 1)
		frame_animation(doom, entity);
	entity->angle = 0;
	if (doom->sprites[entity->tx].nb[entity->state][ANGLES] == 8)
		entity->angle = orientation(entity->where,
					doom->player.where, entity->yaw);
}

void	precompute_entities(t_doom *doom)
{
	int i;
	t_entity *entity;

	i = -1;
	while (++i < doom->nb.entities)
	{
		entity = &doom->entity[i];
		if (!entity->stat.hostile || !entity->render)
			continue ;
		get_entity_state(doom, entity);
		preforme_entiy_state_fuction(doom, entity);
		if (!entity->render)
			continue ;
		get_coresponding_entity_state_frame(doom, entity);
	}
}
