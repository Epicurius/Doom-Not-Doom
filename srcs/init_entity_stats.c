
#include "doom.h"

static void	alfred(t_stats	*alfred)
{
	alfred->hp = 100;
	alfred->dmg = 100;
	alfred->hostile = 1;
	alfred->attack_style = 2;
	alfred->scale = 1;
	alfred->speed = 100;
	alfred->view_distance = 50;
	alfred->detection_radius = 6;
	alfred->attack_range = 4;
	alfred->frame_rate[IDLE] = 100;
	alfred->frame_rate[MOVE] = 100;
	alfred->frame_rate[ATTACK] = 100;
	alfred->frame_rate[DEATH] = 100;
	alfred->flying = 1;
}

static void	spooky(t_stats	*spooky)
{
	spooky->hp = 200;
	spooky->dmg = 30;
	spooky->hostile = 1;
	spooky->attack_style = 1;
	spooky->scale = 2;
	spooky->speed = 100;
	spooky->view_distance = 50;
	spooky->detection_radius = 6;
	spooky->attack_range = 35;
	spooky->frame_rate[IDLE] = 100;
	spooky->frame_rate[MOVE] = 100;
	spooky->frame_rate[ATTACK] = 400;
	spooky->frame_rate[DEATH] = 100;
	spooky->flying = 0;
}

void	init_entity_stats(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < doom->nb.entities)
	{
		if (doom->entity[i].tx == 0)
			alfred(&doom->entity[i].stat);
		else if (doom->entity[i].tx == 1)
			spooky(&doom->entity[i].stat);
	}
}
