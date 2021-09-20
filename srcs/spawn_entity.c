/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_entity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:20:56 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/20 10:36:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	spawn_entity(t_doom *doom, int type, t_v3 pos, int yaw)
{
	t_entity	*mob;

	mob = PROT_ALLOC(sizeof(t_entity));
	mob->type = type;
	mob->yaw = yaw * CONVERT_TO_RADIANS;
	mob->where = pos;
	mob->sector = find_sector(doom->sectors, doom->nb.sectors, pos);
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

/*
 *	Spawn a Alfred, Spooky or Ghost and init it.
 */
static void	spawn_entity_from_rift(t_doom *doom, t_entity *rift)
{
	t_entity	*mob;

	mob = PROT_ALLOC(sizeof(t_entity));
	mob->type = rand() % 3;
	mob->yaw = (rand() % 365) * CONVERT_TO_RADIANS;
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

/*
 *	Loop all the Rifts and spawn a entity.
 */
void	rift_spawn(t_doom *doom)
{
	t_list	*curr;

	curr = doom->entity;
	while (curr)
	{
		if (((t_entity *)curr->content)->type == RIFT)
			spawn_entity_from_rift(doom, curr->content);
		curr = curr->next;
	}
}

/*
 *	Respawn all the Rifts.
 */
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
		doom->nb.entities += 1;
		curr = curr->next;
	}
}
