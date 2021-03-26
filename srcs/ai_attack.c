
#include "doom.h"

void	ai_attack(t_doom *doom, t_entity *entity)
{
	if (entity->frame + 1 < doom->sprites[entity->tx].nb[ATTACK][FRAMES])
		return ;
	if (doom->sprites[entity->tx].nb[DEATH][FRAMES] == 0)
	{
		printf("EXplode\n");
		doom->player.hp -= entity->stat.dmg;
		entity->render = 0;
	}
	else
	{
		printf("Shot\n");
	}
}
