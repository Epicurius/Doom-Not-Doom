
#include "doom.h"
/*
void	object_collision(t_doom *doom, t_player *player)
{
	if (entity->type == AMMO)
		doom->player.ammo += 50;
	else if (object->type == HEALTH)
		doom->player.hp += 50;
	else
		return ;
	entity->render = 0;	
}
*/

int	entity_collision(t_collision_thread *entity, t_xyz dest)
{
	int i;

	i = -1;
	while (++i < entity->nb_entities)
	{
		if (!entity->entities[i].render)
			continue ;
		if (point_distance_3d(entity->entities[i].where, dest)
				> entity->hitbox_radius)
			continue ;
		//if (entity->entities[i].animate)
		//	return (1);
		//else if (player)
		//	object_collision(doom, &doom->entity[i]);
		return (1);
	}
	return (0);
}
