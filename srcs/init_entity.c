/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:30 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/26 17:16:09 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	alfred(t_doom *doom, t_data *alfred)
{
	alfred->health 				= 1;
	alfred->damage 				= 100;
	alfred->animate 			= 1;
	alfred->hostile 			= 1;
	alfred->attack_style 		= 2;
	alfred->scale 				= 4 * (doom->surface->w / 100);
	alfred->height 				= 4;
	alfred->speed 				= 20;
	alfred->move			 	= 1;
	alfred->view_distance 		= 200;
	alfred->detection_radius 	= 40;
	alfred->attack_range 		= 7;
	alfred->frame_rate[IDLE] 	= 2000;
	alfred->frame_rate[MOVE] 	= 4000;
	alfred->frame_rate[ATTACK]	= 6000;
	alfred->frame_rate[DEATH]	= 6000;
	alfred->flying 				= 1;
}

static void	spooky(t_doom *doom, t_data *spooky)
{
	spooky->health 				= 1;
	spooky->damage 				= 30;
	spooky->animate 			= 1;
	spooky->hostile 			= 1;
	spooky->attack_style 		= 1;
	spooky->scale 				= 2 * (doom->surface->w / 100);
	spooky->height 				= 9;
	spooky->speed 				= 10;
	spooky->move			 	= 1;
	spooky->view_distance 		= 100;
	spooky->detection_radius 	= 40;
	spooky->attack_range 		= 200;//80
	spooky->frame_rate[IDLE] 	= 2000;
	spooky->frame_rate[MOVE] 	= 6000;
	spooky->frame_rate[ATTACK] 	= 18000;
	spooky->frame_rate[DEATH] 	= 12000;
	spooky->flying 				= 0;
}

static void	rift(t_doom *doom, t_data *rift)
{
	rift->health 				= 1;
	rift->damage 				= 200;
	rift->attack_style 			= 2;
	rift->scale 				= 2 * (doom->surface->w / 100);
	rift->height 				= 9;
	rift->frame_rate[IDLE] 		= 2000;
	rift->frame_rate[DEATH] 	= 8000;
}

static void	barrel(t_doom *doom, t_data *sprite)
{
	sprite->health 				= 20;
	sprite->scale 				= 5 * (doom->surface->w / 100);
	sprite->frame_rate[DEATH] 	= 6000;
}

static void	lamp(t_doom *doom, t_data *sprite)
{
	sprite->health 				= 11120;
	sprite->scale 				= 5 * (doom->surface->w / 100);
	sprite->frame_rate[IDLE] 	= 3000;
}

static void	torch(t_doom *doom, t_data *sprite)
{
	sprite->health 				= 11120;
	sprite->scale 				= 5 * (doom->surface->w / 100);
	sprite->frame_rate[IDLE] 	= 9000;
}

static void	meat_hook(t_doom *doom, t_data *sprite)
{
	sprite->health 				= 11120;
	sprite->scale 				= 10 * (doom->surface->w / 100);
	sprite->frame_rate[IDLE] 	= 1000;
}

void	init_game_entity(t_doom *doom)
{
	t_list		*new;
	t_list		*curr;
	t_entity	*sprite;

	alfred(doom, &doom->npe_data[0]);
	spooky(doom, &doom->npe_data[1]);
	rift(doom, &doom->npe_data[2]);
	barrel(doom, &doom->npe_data[3]);
	lamp(doom, &doom->npe_data[4]);
	torch(doom, &doom->npe_data[5]);
	meat_hook(doom, &doom->npe_data[6]);
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
