/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:20:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 09:18:40 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	spawn_mob(t_doom *doom, t_entity *rift)
{
	t_entity	*mob;

	mob = protalloc(sizeof(t_entity), "spawn_mob");
	mob->type = rand() % 2;
	mob->yaw = rand() % 365;
	mob->where = rift->where;
	mob->sector = rift->sector;
	mob->dest = mob->where;
	mob->state = IDLE;
	if (g_entity_data[mob->type].flight)
		mob->where.z += 5;
	mob->hp = g_entity_data[mob->type].health;
	project_entity(doom, mob, &mob->render);
	ft_lstadd_new(&doom->entity, mob, sizeof(mob));
	doom->nb.entities += 1;
	doom->game.spawns += 1;
}

void	rift_spawn(t_doom *doom)
{
	t_list	*curr;

	curr = doom->entity;
	while (curr)
	{
		if (((t_entity *)curr->content)->type == 2)
			spawn_mob(doom, curr->content);
		curr = curr->next;
	}
}

void	respawn_rifts(t_doom *doom)
{
	t_list	*new;
	t_list	*curr;

	curr = doom->rifts;
	while (curr != NULL)
	{
		new = ft_lstnew(curr->content, curr->content_size);
		ft_lstadd(&doom->entity, new);
		doom->game.spawns += 1;
		curr = curr->next;
	}
}
