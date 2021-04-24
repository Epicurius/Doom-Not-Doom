
#include "doom.h"

static void	alfred(t_stats *alfred)
{
	alfred->health = 100;
	alfred->damage = 100;
	alfred->animate = 1;
	alfred->hostile = 1;
	alfred->attack_style = 2;
	alfred->scale = 4 * (W / 100);
	alfred->height = 4;
	alfred->speed = 0.02;
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

static void	spooky(t_stats *spooky)
{
	spooky->health = 30;
	spooky->damage = 30;
	spooky->animate = 1;
	spooky->hostile = 1;
	spooky->attack_style = 1;
	spooky->scale = 2 * (W / 100);
	spooky->height = 9;
	spooky->speed = 0.01;
	spooky->wonder_distance = 20;
	spooky->view_distance = 50;
	spooky->detection_radius = 5;
	spooky->attack_range = 35;
	spooky->frame_rate[IDLE] = 100;
	spooky->frame_rate[MOVE] = 200;
	spooky->frame_rate[ATTACK] = 500;
	spooky->frame_rate[DEATH] = 500;
	spooky->flying = 0;
}

void	init_projectiles(t_doom *doom)
{
	int p;
	t_list *curr;
	t_entity *entity;

	doom->orb = ft_memalloc(sizeof(t_projectile)
				* doom->nb.projectiles);
	p = 0;
	curr = doom->entity;
	while (curr)
	{
		entity = curr->content;
		curr = curr->next;
		if (entity->stat.attack_style == 1)
		{
			entity->orb = &doom->orb[p];
			p++;
		}
		else
			entity->orb = NULL;
	}
}
/*
void	init_entity(t_doom *doom)
{
	int i;
	int type;

	i = -1;
	alfred(&doom->entity_stats[0]);
	spooky(&doom->entity_stats[1]);
	while (++i < doom->nb.entities)
	{
		type = doom->entity[i].type;
		doom->entity[i].stat = doom->entity_stats[type];
		doom->entity[i].hp = doom->entity[i].stat.health;
		doom->entity[i].dest = doom->entity[i].where;
		doom->entity[i].sector = find_sector(doom, doom->entity[i].where);
		doom->entity[i].render = 1;
		if (doom->entity[i].stat.attack_style == 1)
			doom->nb.projectiles++;
	}
	if (doom->nb.projectiles > 0)
		init_projectiles(doom);
	doom->player.sector = find_sector(doom, doom->player.where);
	doom->player.hp = 1000;
	doom->player.flying = 0;
}
*/

void	init_entity(t_doom *doom)
{
	int			type;
	t_list		*curr;
	t_entity	*entity;

	alfred(&doom->entity_stats[0]);
	spooky(&doom->entity_stats[1]);
	curr = doom->entity;
	while (curr)
	{
		entity = curr->content;
		curr = curr->next;
		type = entity->type;
		entity->stat = doom->entity_stats[type];
		entity->hp = entity->stat.health;
		entity->dest = entity->where;//
		entity->sector = find_sector(doom, entity->where);
		entity->render = 1;
		if (entity->stat.attack_style == 1)
			doom->nb.projectiles++;
	}
	if (doom->nb.projectiles > 0)
		init_projectiles(doom);
	doom->player.sector = find_sector(doom, doom->player.where);
	doom->player.hp = 1000;
	doom->player.flying = 0;
}
