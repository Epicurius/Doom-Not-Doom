
#include "doom.h"

void	frame_animation(t_doom *doom, t_entity *entity)
{
	if (entity->time - doom->fps.curr < -(entity->stat.frame_rate[entity->state]))
	{
		entity->frame++;
		entity->time = doom->fps.curr;
	}
	if (entity->frame >= doom->sprites[entity->type].nb[entity->state][FRAMES])
	{
		if (entity->state == DEATH)
			entity->render = 0;
		entity->frame = 0;
	}
		
}

int	entity_see(t_doom *doom, t_entity *entity)
{
	double left;
	double right;
	t_xyz	far_left;
	t_xyz	far_right;

	left = entity->yaw + 65;
	right = entity->yaw - 65;
	if (left > 360)
		left -= 360;
	if (right < 0)
		right += 360;
	left = (left * CONVERT_RADIANS);
	right = (right * CONVERT_RADIANS);
	far_left.x =  1000 * cos(left)  + entity->where.x;
	far_left.y =  1000 * sin(left)  + entity->where.y;
	far_right.x = 1000 * cos(right) + entity->where.x;
	far_right.y = 1000 * sin(right) + entity->where.y;
	left = point_side(far_left, entity->where, doom->player.where);
	right = point_side(entity->where, far_right, doom->player.where);
	if (left > 0 && right > 0)
		return (1);
	return (0);
}
/*
int	entity_see(t_doom *doom, t_entity *entity, double dist)
{
	int left;
	int right;

	left = point_side(entity->far_left, entity->where, doom->player.where);
	right = point_side(entity->where, entity->far_right, doom->player.where);
	if (left > 0 && right > 0)
		return (1);
	return (0);
}
*/
int	entity_line_of_sight(t_doom *doom, t_entity *entity, double dist)
{
	if (dist > entity->stat.view_distance)
		return (0);
	if (dist < entity->stat.detection_radius)
		return (1);
	//entity_fov(doom, entity);
	if (entity_see(doom, entity))
		return (2);
	return (0);
}

void	get_entity_state(t_doom *doom, t_entity *entity)
{
	double dist;

	if (entity->stat.hp < 0)
		entity->state = DEATH;
	if (entity->frame != 0)
		return ;
	dist = point_distance_2d(entity->where.x, entity->where.y,
			doom->player.where.x, doom->player.where.y);
	if (entity_line_of_sight(doom, entity, dist))
	{
		if (entity->stat.attack_range > dist)
			entity->state = ATTACK;
		else
		{
			entity->dest = doom->player.where;
			entity->state = MOVE;
		}
	}
	else
	{
		if (entity->stat.wonder_distance > 0 && ai_rand_move(entity, rand() % 40000))
			entity->state = MOVE;
		else
			entity->state = IDLE;
	}
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
	if (doom->sprites[entity->type].nb[entity->state][FRAMES] > 1)
	{
		if (entity->stat.attack_style == 1 && entity->orb->render)
			entity->frame = 0;
		else
			frame_animation(doom, entity);
	}
	entity->angle = orientation(entity->where, doom->player.where,
		entity->yaw, doom->sprites[entity->type].nb[entity->state][ANGLES]);
}

void	precompute_entities(t_doom *doom)
{
	int i;
	t_entity *entity;

	i = -1;
	while (++i < doom->nb.entities)
	{
		entity = &doom->entity[i];
		if (!entity->stat.animate || !entity->render)
			continue ;
		get_entity_state(doom, entity);
		preforme_entiy_state_fuction(doom, entity);
		if (!entity->render)
			continue ;
		get_coresponding_entity_state_frame(doom, entity);
	}
}
