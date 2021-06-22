/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:37:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/22 12:21:18 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_hud(t_doom *doom)
{
	hud_health(doom);
	hud_armour(doom);
	hud_curr_ammo(doom);
	hud_mag_ammo(doom);
	hud_dosh(doom);
}