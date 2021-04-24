
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

int	entity_collision(t_collision *e, t_xyz dest)
{
	t_list *curr;
	t_entity *entities;

	curr = e->entities;
	while (curr)
	{
		entities = curr->content;
		curr = curr->next;
		if (!entities->render)
			continue ;
		if (point_distance_3d(entities->where, dest) > (e->hitbox_radius + 3))
			continue ;
		//if (entity->entities[i].animate)
		//	return (1);
		//else if (player)
		//	object_collision(doom, &doom->entity[i]);
		return (1);
	}
	return (0);
}
