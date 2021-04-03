
#include "doom.h"

static void	alfred(t_stats	*alfred)
{
	alfred->hp = 100;
	alfred->dmg = 100;
	alfred->animate = 1;
	alfred->hostile = 1;
	alfred->attack_style = 2;
	alfred->scale = 50;
	alfred->height = 4;
	alfred->speed = 0.05;
	alfred->wonder_distance = 0;
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
	spooky->animate = 1;
	spooky->hostile = 1;
	spooky->attack_style = 1;
	spooky->scale = 25;
	spooky->height = 9;
	spooky->speed = 0.01;
	spooky->wonder_distance = 20;
	spooky->view_distance = 50;
	spooky->detection_radius = 5;
	spooky->attack_range = 35;
	spooky->frame_rate[IDLE] = 100;
	spooky->frame_rate[MOVE] = 200;
	spooky->frame_rate[ATTACK] = 400;
	spooky->frame_rate[DEATH] = 500;
	spooky->flying = 0;
}

void	init_projectiles(t_doom *doom)
{
	int p;
	int i;

	doom->orb = ft_memalloc(sizeof(t_projectile)
				* doom->nb.projectiles);
	p = 0;
	i = -1;
	while (++i < doom->nb.entities)
	{
		if (doom->entity[i].stat.attack_style == 1)
		{
			doom->entity[i].orb = &doom->orb[p];
			p++;
		}
	}
}

void	init_entity_stats(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < doom->nb.entities)
	{
		if (doom->entity[i].type == ALFRED)
			alfred(&doom->entity[i].stat);
		else if (doom->entity[i].type == SPOOKY)
			spooky(&doom->entity[i].stat);
		if (doom->entity[i].stat.attack_style == 1)
			doom->nb.projectiles++;
		doom->entity[i].dest = doom->entity[i].where;
	}
//	printf("%d\n", doom->nb.projectiles);
	if (doom->nb.projectiles > 0)
		init_projectiles(doom);
}
