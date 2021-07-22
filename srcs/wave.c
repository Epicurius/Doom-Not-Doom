/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:58:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/22 19:23:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	spawn_mob(t_doom *doom, t_entity *rift)
{
	t_entity	*mob;

	mob = ft_memalloc(sizeof(t_entity));
	mob->type = rand() % 2;
	mob->yaw = rand() % 365;
	mob->where = rift->where;
	mob->sector = rift->sector;
	mob->dest = mob->where;
	mob->state = IDLE;
	if (g_entity_data[mob->type].flying)
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

int	eternal_round(t_doom *doom)
{
	if (doom->game.spawns == 0)
	{
		doom->game.round++;
		doom->game.spawn_rate -= 200;
		return (1);
	}
	else if (doom->game.time - doom->time.curr < -(doom->game.spawn_rate))
	{
		rift_spawn(doom);
		doom->game.time = doom->time.curr;
	}
	return (0);
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

void	game_mode(t_doom *doom)
{
	int i;

	i = -1;
	if (doom->game.cool_down)
	{
		doom->game.cool_down -= 1 * doom->time.delta;
		if (doom->game.cool_down <= 0)
		{
			doom->player.store_access = 0;
			while (++i < doom->nb.events)
				if (doom->events[i].type == STORE)
					doom->events[i].wsprite->src = rect_xy2(662, 0, 1324, 550);
			respawn_rifts(doom);
		}
	}
	else if (!Mix_Playing(CHANNEL_TTS) && eternal_round(doom))
	{
		doom->game.cool_down = 1000;
		doom->player.hp = 200;
		doom->player.store_access = 1;
		while (++i < doom->nb.events)
			if (doom->events[i].type == STORE)
				doom->events[i].wsprite->src = rect_xy2(0, 0, 662, 550);
	}
}
