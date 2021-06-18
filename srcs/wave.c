/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wave.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 10:58:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 16:41:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_gamemode(t_doom *doom)
{
	doom->game.round = 0;
	doom->game.spawns = doom->nb.sprites;
	doom->game.time = doom->time.curr;
	doom->game.spawn_rate = 5000;
	doom->game.cool_down = 0;
}

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
	mob->data = &doom->npe_data[mob->type];
	if (mob->data->flying)
		mob->where.z += 5;
	mob->hp = mob->data->health;
	project_entity(doom, mob, &mob->render);
	ft_lstadd_new(&doom->sprite, mob, sizeof(mob));
	doom->nb.sprites += 1;
	doom->game.spawns += 1;
}

void	rift_spawn(t_doom *doom)
{
	t_list	*curr;

	curr = doom->sprite;
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
		ft_printf("Round: %d\n", doom->game.round);
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
		ft_lstadd(&doom->sprite, new);
		doom->game.spawns += 1;
		curr = curr->next;
	}
}

void	gamemode(t_doom *doom)
{
	if (doom->game.cool_down)
	{
		doom->game.cool_down -= 1;
		if (doom->game.cool_down <= 0)
			respawn_rifts(doom);
	}
	else if (doom->intro && eternal_round(doom))
		doom->game.cool_down = 1000;
}
