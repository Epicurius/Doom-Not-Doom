
#include "doom.h"

void	frame_animation(t_doom *doom, t_sprite *entity)
{
	if (entity->time - doom->fps.curr < -(entity->stat.frame_rate[entity->state]))
	{
		entity->frame++;
		entity->time = doom->fps.curr;
	}
	if (entity->frame >= doom->sheet[entity->type].nb[entity->state][FRAMES])
	{
		if (entity->state == DEATH)
			entity->render = 0;
		entity->frame = 0;
	}
		
}

int		entity_see(t_doom *doom, t_sprite *entity)
{
	t_xyz	far_left;
	t_xyz	far_right;

	far_left.z	= entity->yaw + 65;
	far_right.z	= entity->yaw - 65;
	far_left.z	-= far_left.z > 360 ? 360 : 0;
	far_right.z	+= far_right.z < 0 ? 360 : 0;
	far_left.z	= (far_left.z * CONVERT_RADIANS);
	far_right.z	= (far_right.z * CONVERT_RADIANS);
	far_left.x	= 1000 * cos(far_left.z)  + entity->where.x;
	far_left.y	= 1000 * sin(far_left.z)  + entity->where.y;
	far_right.x	= 1000 * cos(far_right.z) + entity->where.x;
	far_right.y	= 1000 * sin(far_right.z) + entity->where.y;
	far_left.z	= point_side(far_left, entity->where, doom->player.where);
	far_right.z	= point_side(entity->where, far_right, doom->player.where);
	if (far_left.z > 0 && far_right.z > 0)
		return (1);
	return (0);
}

int		entity_line_of_sight(t_doom *doom, t_sprite *entity, double dist)
{
	if (dist > entity->stat.view_distance)
		return (0);
	if (dist < entity->stat.detection_radius)
		return (1);
	if (entity_see(doom, entity))
		return (2);
	return (0);
}

void	get_entity_state(t_doom *doom, t_sprite *entity)
{
	double dist;

	if (entity->frame != 0)
		return ;
	if (entity->hp <= 0)
	{
		entity->state = DEATH;
		return ;
	}
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

void	preforme_entity_state_fuction(t_doom *doom, t_sprite *entity)
{
	if (entity->state == MOVE)
		ai_movement(doom, entity);
	else if (entity->state == ATTACK)
		ai_attack(doom, entity);
}

void	get_coresponding_entity_state_frame(t_doom *doom, t_sprite *entity)
{
	if (doom->sheet[entity->type].nb[entity->state][FRAMES] > 1)
			frame_animation(doom, entity);
	entity->angle = orientation(entity->where, doom->player.where,
		entity->yaw, doom->sheet[entity->type].nb[entity->state][ANGLES]);
}

void	precompute_entities(t_doom *doom)
{
	t_list		*curr;
	t_sprite	*entity;

	curr = doom->entity;
	while (curr)
	{
		entity = curr->content;
		curr = curr->next;
		if (!entity->stat.animate || !entity->render)
			continue ;
		get_entity_state(doom, entity);
		preforme_entity_state_fuction(doom, entity);
		if (!entity->render)
			continue ;
		get_coresponding_entity_state_frame(doom, entity);
	}
}
