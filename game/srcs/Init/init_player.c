/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	init_player(t_doom *doom)
{
	doom->player.where.z = ft_fmax(doom->player.where.z,
			floor_at(&doom->sectors[doom->player.sector], doom->player.where));
	doom->player.max_hp = 1100 - doom->settings.difficulty * 100;
	doom->player.health = doom->player.max_hp;
	doom->player.armour = 1000 - doom->settings.difficulty * 100;
	doom->player.eyelvl = EYE_LVL;
	doom->player.flight = doom->settings.debug;
	doom->player.debug = doom->settings.debug;
	doom->player.equipped = START_WEAPON;
	doom->player.walk_speed = WALK_SPEED;
	doom->player.sprint_speed = SPRINT_SPEED;
	doom->player.jump_height = JUMP_HEIGHT;
}
