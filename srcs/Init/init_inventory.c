/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:11:55 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/24 10:13:33 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_inventory(t_doom *doom)
{
	doom->inv.dosh = 1000;
	doom->inv.max_armour_price = 100;
	doom->inv.speed_price = 101;
	doom->inv.jump_price = 102;
	doom->inv.armour_price = 103;
	doom->inv.max_armour = 100;
	doom->inv.weapon = doom->weapon;
	doom->inv.hp = &doom->player.health;
	doom->inv.armour = &doom->player.armour;
	doom->inv.speed = &doom->player.sprint_speed;
	doom->inv.jump = &doom->player.jump_height;
}
