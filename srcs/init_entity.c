
#include "doom.h"

static void	alfred(t_npe_data *alfred)
{
	alfred->health 				= 100;
	alfred->damage 				= 100;
	alfred->animate 			= 1;
	alfred->hostile 			= 1;
	alfred->attack_style 		= 2;
	alfred->scale 				= 4 * (W / 100);
	alfred->height 				= 4;
	alfred->speed 				= 0.02;
	alfred->wonder_distance 	= 0;
	alfred->view_distance 		= 50;
	alfred->detection_radius 	= 6;
	alfred->attack_range 		= 4;
	alfred->frame_rate[IDLE] 	= 100;
	alfred->frame_rate[MOVE] 	= 100;
	alfred->frame_rate[ATTACK]	 = 100;
	alfred->frame_rate[DEATH]	 = 100;
	alfred->flying 				= 1;
}

static void	spooky(t_npe_data *spooky)
{
	spooky->health 				= 30;
	spooky->damage 				= 30;
	spooky->animate 			= 1;
	spooky->hostile 			= 1;
	spooky->attack_style 		= 1;
	spooky->scale 				= 2 * (W / 100);
	spooky->height 				= 9;
	spooky->speed 				= 0.01;
	spooky->wonder_distance 	= 20;
	spooky->view_distance 		= 50;
	spooky->detection_radius 	= 5;
	spooky->attack_range 		= 35;
	spooky->frame_rate[IDLE] 	= 100;
	spooky->frame_rate[MOVE] 	= 200;
	spooky->frame_rate[ATTACK] 	= 500;
	spooky->frame_rate[DEATH] 	= 500;
	spooky->flying 				= 0;
}

static void	rift(t_npe_data *rift)
{
	rift->health 				= 500;
	rift->damage 				= 200;
	rift->attack_style 		= 2;
	rift->scale 				= 1.3 * (W / 100);
	rift->height 				= 9;
}

void	init_sprite(t_doom *doom)
{
	t_list		*curr;
	t_sprite	*sprite;

	alfred(&doom->npe_data[0]);
	spooky(&doom->npe_data[1]);
	rift(&doom->npe_data[2]);
	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		curr = curr->next;
		sprite->data = &doom->npe_data[sprite->type];
		sprite->hp = sprite->data->health;
		sprite->sector = find_sector(doom, sprite->where);
		sprite->dest = sprite->where;
		sprite->render = 1;
	}
}
