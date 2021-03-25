
#include "doom.h"

void	move_entity(t_doom *doom, t_entity *entity)
{
	//if (doom->entity.attack_style == STYLE_MELEE)
	melee_ai(doom, entity);
	//else if (doom->entity.attack_style == RANGE)
		//range_ai();
}

void	attack_animation(t_doom *doom, t_entity *entity)
{
	if (entity->time - doom->fps.curr < -100)
	{
		if (entity->frame < 8)//entity->attack_frame_start)
			entity->frame = 8;//entity->attack_frame_start;
		else
			entity->frame++;
		entity->time = doom->fps.curr;
	}
	if (entity->frame == 14)//entity->attack_frame_end)
		entity->ready = 0;
		
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
	//printf("Yaw %f %f %f\n", entity->yaw, left, right);
	entity->far_left.x = 1000 * cos(left) + entity->where.x;
	entity->far_left.y = 1000 * sin(left) + entity->where.y;
	entity->far_right.x = 1000 * cos(right) + entity->where.x;
	entity->far_right.y = 1000 * sin(right) + entity->where.y;
}

int	entity_see(t_doom *doom, t_entity *entity, double dist)
{
	int l;
	int r;

	if (dist > 50) //Fov cone length
		return (0);
	l = point_side(entity->far_left, entity->where, doom->player.where);
	r = point_side(entity->where, entity->far_right, doom->player.where);
	if (l > 0 && r > 0)
		return (1);
	return (0);
	//side = point_side(entity->far_left, entity->far_right, doom->player.where);
}

int	entity_line_of_sight(t_doom *doom, t_entity *entity, double dist)
{
	entity_fov(doom, entity);
	if (entity_see(doom, entity, dist))
		return (1);
	if (dist < 6) //Detection Radius
		return (2);
	return (0);
	//printf("%d\n", entity_see(doom, entity, dist));
}

void	precompute_entities(t_doom *doom)
{
	int i;
	double dist;
	t_entity *entity;

	i = -1;
	while (++i < doom->nb.entities)
	{
		entity = &doom->entity[i];
		if (entity->mood || !entity->ready)
			continue ;
		dist = point_distance_2d(entity->where.x, entity->where.y,
				doom->player.where.x, doom->player.where.y);
		if (dist > 50)
			entity->state = IDLE;
		else if (dist < 4)
			entity->state = IDLE;
		else if (entity_line_of_sight(doom, entity, dist))
			entity->state = MOVE;
	
		if (entity->state == MOVE) //close
			move_entity(doom, entity);
		else if (entity->state == ATTACK)
		{
			attack_animation(doom, entity);
			continue ;
		}
		entity->frame = 0;
		if (doom->sprites[0].nb[entity->state][ANGLES] == 8)
			entity->angle = orientation(entity->where, doom->player.where, entity->yaw);
		else
			entity->angle = 0;
	}
}
