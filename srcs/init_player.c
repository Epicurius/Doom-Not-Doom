/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/20 13:03:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_player(t_doom *doom)
{
	doom->player.sector = find_sector(doom, doom->player.where);
	doom->player.hp = 1000;
	doom->player.armour = 100;
	doom->player.flying = 0;
	doom->player.equiped = 0;
	doom->player.walk_speed = WALK_SPEED;
	doom->player.sprint_speed = SPRINT_SPEED;
	doom->player.jump_height = 0.0f;
}
