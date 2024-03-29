/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static void	weapon_texture_array(t_doom *doom)
{
	int	i;

	i = -1;
	while (++i < WEAPON_AMOUNT)
	{
		doom->weapon[i].bxpm = malloc(sizeof(t_bxpm)
				* (doom->weapon[i].fire_frames
					+ doom->weapon[i].reload_frames));
		if (!doom->weapon[i].bxpm)
			LG_ERROR("Weapon bxpm array nb %d.", i);
	}
}

void	init_weapons(t_doom *doom)
{
	init_shotgun(doom, &doom->weapon[WEAPON_SHOTGUN]);
	init_glock(doom, &doom->weapon[WEAPON_GUN]);
	init_minigun(doom, &doom->weapon[WEAPON_MINIGUN]);
	init_kar98(doom, &doom->weapon[WEAPON_KAR]);
	init_launcher(doom, &doom->weapon[WEAPON_LAUNCHER]);
	weapon_texture_array(doom);
}
