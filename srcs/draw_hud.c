/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 10:37:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 10:38:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_hud(t_doom *doom)
{
	hud_health(doom);
	hud_armour(doom);
	hud_currammo(doom);
	hud_magammo(doom);
	hud_dosh(doom);
}
