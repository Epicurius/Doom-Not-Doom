
#include "doom.h"

int	ai_rand_move(t_sprite *entity, int rand)
{
	double angle;

	if (rand > 360 || rand < 0)
		return (0);
	angle = rand * CONVERT_RADIANS;
	entity->dest.x = (entity->stat.wonder_distance * cos(angle));
	entity->dest.y = (entity->stat.wonder_distance * sin(angle));
	entity->dest.x += entity->where.x;
	entity->dest.y += entity->where.y;
	entity->dest.z = entity->where.z;
	return (1);
}
