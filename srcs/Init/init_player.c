/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/08 15:23:30 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_player(t_doom *doom)
{
	doom->player.where.z = ft_fmax(doom->player.where.z,
			floor_at(&doom->sectors[doom->player.sector], doom->player.where));
	doom->player.health = 1100 - doom->settings.difficulty * 100;
	doom->player.armour = 1000 - doom->settings.difficulty * 100;
	doom->player.eyelvl = EYE_LVL;
	doom->player.flight = FALSE;
	doom->player.debug = doom->settings.debug;
	doom->player.equipped = 0;
	doom->player.walk_speed = WALK_SPEED;
	doom->player.sprint_speed = SPRINT_SPEED;
	doom->player.jump_height = JUMP_HEIGHT;
}
