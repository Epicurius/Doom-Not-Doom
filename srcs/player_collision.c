/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:33:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/24 15:33:54 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	player_collision(t_doom *doom)
{
	t_collision p;

	p.where				= &doom->player.where;
	p.velocity			= &doom->player.velocity;
	p.sector			= &doom->player.sector;
	p.sectors			= doom->sectors;
	p.entities			= doom->sprite;
	p.nb_entities		= doom->nb.entities;
	p.player			= 1;
	p.hitbox_height		= PLAYER_HEIGHT;
	p.hitbox_radius		= PLAYER_RADIUS;
	p.step_height		= STEP_HEIGHT;
	collision_detection(&p);
}
