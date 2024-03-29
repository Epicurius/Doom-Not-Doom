/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static void	init_entity_pos(t_doom *doom)
{
	init_alfred(doom);
	init_spooky(doom);
	init_rift(doom);
	init_barrel(doom);
	init_lamp(doom);
	init_torch(doom);
	init_meat_hook(doom);
	init_ghost(doom);
	init_ceiling_lamp(doom);
	init_gargoyle(doom);
	init_med_kit(doom);
}

void	init_entities(t_doom *doom)
{
	t_list		*new;
	t_list		*curr;
	t_entity	*entity;

	init_entity_pos(doom);
	curr = doom->entity;
	while (curr)
	{
		entity = curr->content;
		entity->hp = g_entity_data[entity->type].health;
		entity->dest = entity->where;
		entity->state = IDLE;
		if (doom->game.mode == ENDLESS && entity->type == RIFT)
		{
			new = ft_lstnew(curr->content, sizeof(t_entity));
			ft_lstadd(&doom->rifts, new);
			doom->nb.rifts += 1;
		}
		curr = curr->next;
	}
}
