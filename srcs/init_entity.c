
#include "doom.h"

static void	alfred(t_doom *doom, t_game_data *alfred)
{
	alfred->health 				= 1;
	alfred->damage 				= 100;
	alfred->animate 			= 1;
	alfred->hostile 			= 1;
	alfred->attack_style 		= 2;
	alfred->scale 				= 4 * (doom->surface->w / 100);
	alfred->height 				= 4;
	alfred->speed 				= 0.07;
	alfred->wonder_distance 	= 0;
	alfred->view_distance 		= 100;
	alfred->detection_radius 	= 6;
	alfred->attack_range 		= 4;
	alfred->frame_rate[IDLE] 	= 100;
	alfred->frame_rate[MOVE] 	= 100;
	alfred->frame_rate[ATTACK]	 = 100;
	alfred->frame_rate[DEATH]	 = 100;
	alfred->flying 				= 1;
}

static void	spooky(t_doom *doom, t_game_data *spooky)
{
	spooky->health 				= 1;
	spooky->damage 				= 30;
	spooky->animate 			= 1;
	spooky->hostile 			= 1;
	spooky->attack_style 		= 1;
	spooky->scale 				= 2 * (doom->surface->w / 100);
	spooky->height 				= 9;
	spooky->speed 				= 0.03;
	spooky->wonder_distance 	= 40;
	spooky->view_distance 		= 120;
	spooky->detection_radius 	= 5;
	spooky->attack_range 		= 80;
	spooky->frame_rate[IDLE] 	= 100;
	spooky->frame_rate[MOVE] 	= 200;
	spooky->frame_rate[ATTACK] 	= 500;
	spooky->frame_rate[DEATH] 	= 500;
	spooky->flying 				= 0;
}

static void	rift(t_doom *doom, t_game_data *rift)
{
	rift->health 				= 1;
	rift->damage 				= 200;
	rift->attack_style 			= 2;
	rift->scale 				= 2 * (doom->surface->w / 100);
	rift->height 				= 9;
	rift->frame_rate[IDLE] 		= 100;
	rift->frame_rate[DEATH] 	= 700;
}

void	init_game_entity(t_doom *doom)
{
	t_list		*new;
	t_list		*curr;
	t_game_entity	*sprite;

	alfred(doom, &doom->npe_data[0]);
	spooky(doom, &doom->npe_data[1]);
	rift(doom, &doom->npe_data[2]);
	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		sprite->data = &doom->npe_data[sprite->type];
		sprite->hp = sprite->data->health;
		sprite->sector = find_sector(doom, sprite->where);
		sprite->dest = sprite->where;
		sprite->state = IDLE;
		sprite->render = 1;
		if (sprite->type == 2)
		{
			new = ft_lstnew(curr->content, sizeof(t_game_entity));
			ft_lstadd(&doom->rifts, new);
			doom->nb.rifts += 1;
		}
		curr = curr->next;
	}
}
