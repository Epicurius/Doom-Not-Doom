/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

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
