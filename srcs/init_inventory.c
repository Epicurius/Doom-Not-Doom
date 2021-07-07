/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:11:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/07 11:29:04 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_inventory(t_doom *doom)
{
	doom->inv.dosh = 0;
	doom->inv.hp = &doom->player.hp;
	doom->inv.armour = &doom->player.armour;
	doom->inv.max_armour = *doom->inv.armour;
	doom->inv.max_armour_price = 600;
	doom->inv.speed_price = 601;
	doom->inv.jump_price = 602;
	doom->inv.armour_price = 603;
	doom->inv.weapon = doom->weapon;
	doom->inv.speed = &doom->player.sprint_speed;
	doom->inv.jump = &doom->player.jump_height;
}
