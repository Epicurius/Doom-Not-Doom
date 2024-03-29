/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static inline void	calulate_health(t_doom *doom, t_player *player)
{
	Mix_PlayChannel(-1, doom->sound[WAV_PLAYER_HIT], 0);
	if (player->armour)
	{
		player->health += player->armour - player->damage * ARMOR_DMG_REDUCTION;
		player->armour = ft_max(player->health - player->max_hp, 0);
		player->health = ft_min(player->health, player->max_hp);
	}
	else
		player->health -= player->damage;
	player->damage = 0;
}

/*
 *	Prepare the position of the HUD icons and call each of them to be drawn.
 */
void	draw_hud(t_doom *doom)
{
	SDL_Rect	dstr;

	if (doom->player.damage && !doom->player.debug)
		calulate_health(doom, &doom->player);
	dstr.x = 10;
	dstr.y = doom->surface->h;
	hud_health(doom, &dstr);
	hud_armour(doom, &dstr);
	hud_curr_ammo(doom, &dstr);
	hud_mag_ammo(doom, &dstr);
	hud_dosh(doom, &dstr);
}
