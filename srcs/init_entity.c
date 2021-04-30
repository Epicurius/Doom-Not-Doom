
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
/*
void	init_projectiles(t_doom *doom)
{
	int p;
	t_list *curr;
	t_sprite *sprite;

	doom->orb = ft_memalloc(sizeof(t_projectile)
				* doom->nb.projectiles);
	p = 0;
	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		curr = curr->next;
		if (sprite->stat.attack_style == 1)
		{
			sprite->orb = &doom->orb[p];
			p++;
		}
		else
			sprite->orb = NULL;
	}
}
*/
void	init_sprite(t_doom *doom)
{
	int			type;
	t_list		*curr;
	t_sprite	*sprite;

	alfred(&doom->sprite_stats[0]);
	spooky(&doom->sprite_stats[1]);
	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		curr = curr->next;
		type = sprite->type;
		sprite->stat = doom->sprite_stats[type];
		sprite->hp = sprite->stat.health;
		sprite->dest = sprite->where;//
		sprite->sector = find_sector(doom, sprite->where);
		sprite->render = 1;
		//if (sprite->stat.attack_style == 1)
		//	doom->nb.projectiles++;
	}
	//if (doom->nb.projectiles > 0)
	//	init_projectiles(doom);
	{
		doom->player.sector = find_sector(doom, doom->player.where);
		doom->player.hp = 1000;
		doom->player.flying = 0;
	}
}
