/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:30 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/07 12:49:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	init_gargoyl(doom);
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
		if (entity->type == RIFT)
		{
			new = ft_lstnew(curr->content, sizeof(t_entity));
			ft_lstadd(&doom->rifts, new);
			doom->nb.rifts += 1;
		}
		curr = curr->next;
	}
}
