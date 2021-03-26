
#include "doom.h"

void	ai_attack(t_doom *doom, t_entity *entity)
{
	if (entity->frame + 1 < doom->sprites[entity->type].nb[ATTACK][FRAMES])
		return ;
	if (doom->sprites[entity->type].nb[DEATH][FRAMES] == 0)
	{
		printf("EXplode\n");
		doom->player.hp -= entity->stat.dmg;
		entity->render = 0;
	}
	else if (!entity->orb->render)
	{
		entity->orb->render = 1;
		entity->orb->curr = entity->where;	
		entity->orb->dest = doom->player.where;	
		printf("Shot\n");
	}
}
