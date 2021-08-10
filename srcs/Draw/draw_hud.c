/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:37:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 12:04:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_hud(t_doom *doom)
{
	SDL_Rect	dstr;

	dstr.x = 10;
	dstr.y = doom->surface->h;
	hud_health(doom, &dstr);
	hud_armour(doom, &dstr);
	hud_curr_ammo(doom, &dstr);
	hud_mag_ammo(doom, &dstr);
	hud_dosh(doom, &dstr);
}
