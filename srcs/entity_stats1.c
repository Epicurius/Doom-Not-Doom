/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_stats1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:09:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/21 13:50:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	alfred(t_doom *doom, t_data *alfred)
{
	alfred->health = 1;
	alfred->damage = 100;
	alfred->animate = 1;
	alfred->hostile = 1;
	alfred->attack_style = 2;
	alfred->scale = 4 * (doom->surface->w / 100);
	alfred->height = 2;
	alfred->hitbox_radius = 2;
	alfred->speed = 20;
	alfred->move = 1;
	alfred->view_distance = 200;
	alfred->detection_radius = 40;
	alfred->attack_range = 7;
	alfred->frame_rate[IDLE] = 2000;
	alfred->frame_rate[MOVE] = 4000;
	alfred->frame_rate[ATTACK] = 6000;
	alfred->frame_rate[DEATH] = 6000;
	alfred->flying = 1;
}

void	spooky(t_doom *doom, t_data *spooky)
{
	spooky->health = 1;
	spooky->damage = 30;
	spooky->animate = 1;
	spooky->hostile = 1;
	spooky->attack_style = 1;
	spooky->scale = 2 * (doom->surface->w / 100);
	spooky->height = 7;
	spooky->hitbox_radius = 2;
	spooky->speed = 10;
	spooky->move = 1;
	spooky->view_distance = 100;
	spooky->detection_radius = 40;
	spooky->attack_range = 50;
	spooky->frame_rate[IDLE] = 2000;
	spooky->frame_rate[MOVE] = 6000;
	spooky->frame_rate[ATTACK] = 18000;
	spooky->frame_rate[DEATH] = 12000;
	spooky->flying = 0;
}
