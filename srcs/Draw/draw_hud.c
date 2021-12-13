/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:37:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/13 14:42:48 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	calulate_armour_damage_reduction(t_doom *doom)
{
	doom->player.health += doom->player.armour;
	doom->player.armour = ft_max(doom->player.health - doom->player.max_hp, 0);
	doom->player.health = ft_min(doom->player.health, doom->player.max_hp);
}

/*
 *	Prepare the position of the HUD icons and call each of them to be drawn.
 */
void	draw_hud(t_doom *doom)
{
	SDL_Rect	dstr;

	if (doom->player.health < doom->player.max_hp && doom->player.armour)
		calulate_armour_damage_reduction(doom);
	dstr.x = 10;
	dstr.y = doom->surface->h;
	hud_health(doom, &dstr);
	hud_armour(doom, &dstr);
	hud_curr_ammo(doom, &dstr);
	hud_mag_ammo(doom, &dstr);
	hud_dosh(doom, &dstr);
}
