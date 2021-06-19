/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:30 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/19 17:15:32 by nneronin         ###   ########.fr       */
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

static void	init_entity_stats(t_doom *doom)
{
	alfred(doom, &doom->npe_data[0]);
	spooky(doom, &doom->npe_data[1]);
	rift(doom, &doom->npe_data[2]);
	barrel(doom, &doom->npe_data[3]);
	lamp(doom, &doom->npe_data[4]);
	torch(doom, &doom->npe_data[5]);
	meat_hook(doom, &doom->npe_data[6]);
}

void	init_game_entity(t_doom *doom)
{
	t_list		*new;
	t_list		*curr;
	t_entity	*sprite;

	init_entity_pos(doom);
	init_entity_stats(doom);
	curr = doom->sprite;
	while (curr)
	{
		sprite = curr->content;
		sprite->data = &doom->npe_data[sprite->type];
		sprite->hp = sprite->data->health;
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
