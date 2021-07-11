/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_stats2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:09:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 15:52:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rift(t_doom *doom, t_data *rift)
{
	rift->health = 1;
	rift->damage = 200;
	rift->attack_style = 2;
	rift->scale = 2 * (doom->surface->w / 100);
	rift->height = 9;
	rift->frame_rate[IDLE] = 2000;
	rift->frame_rate[DEATH] = 8000;
}

void	barrel(t_doom *doom, t_data *entity)
{
	entity->health = 20;
	entity->scale = 5 * (doom->surface->w / 100);
	entity->frame_rate[DEATH] = 6000;
}

void	lamp(t_doom *doom, t_data *entity)
{
	entity->health = 11120;
	entity->scale = 5 * (doom->surface->w / 100);
	entity->frame_rate[IDLE] = 3000;
}

void	torch(t_doom *doom, t_data *entity)
{
	entity->health = 11120;
	entity->scale = 5 * (doom->surface->w / 100);
	entity->frame_rate[IDLE] = 9000;
}

void	meat_hook(t_doom *doom, t_data *entity)
{
	entity->health = 11120;
	entity->scale = 10 * (doom->surface->w / 100);
	entity->frame_rate[IDLE] = 1000;
}
