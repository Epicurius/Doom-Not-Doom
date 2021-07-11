/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:30 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 14:22:06 by nneronin         ###   ########.fr       */
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
}

void	init_entities(t_doom *doom)
{
	t_list		*new;
	t_list		*curr;
	t_entity	*sprite;

	init_entity_pos(doom);
	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		sprite->hp = g_entity_data[sprite->type].health;
		sprite->dest = sprite->where;
		sprite->state = IDLE;
		if (sprite->type == 2)
		{
			new = ft_lstnew(curr->content, sizeof(t_entity));
			ft_lstadd(&doom->rifts, new);
			doom->nb.rifts += 1;
		}
		curr = curr->next;
	}
}
