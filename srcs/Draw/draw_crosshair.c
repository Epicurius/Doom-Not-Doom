/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/10 18:13:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	If player hit enemy draw diagonal crosshair in green.
 */
static void	draw_hit_marker(t_doom *doom)
{
	if (!doom->player.hm)
		return ;
	Mix_PlayChannel(CHANNEL_ENEMY, doom->sound[WAV_MONSTER_HIT], 0);
	draw_line(doom->surface, 0xff00ff00,
		(t_point){doom->c.x - 10, doom->c.y - 10},
		(t_point){doom->c.x + 10, doom->c.y + 10});
	draw_line(doom->surface, 0xff00ff00,
		(t_point){doom->c.x - 10, doom->c.y + 10},
		(t_point){doom->c.x + 10, doom->c.y - 10});
	doom->player.hm = FALSE;
}

/*
 *	Draw crosshair if equipped weapon is not launcher.
 */
void	draw_crosshair(t_doom *doom)
{
	int		y;
	int		x;
	Uint32	*pixels;

	if (doom->player.equipped == WEAPON_LAUNCHER)
		return ;
	pixels = doom->surface->pixels;
	x = doom->c.x;
	y = doom->c.y - 10 - 1;
	while (++y < doom->c.y - 2)
		pixels[y * doom->surface->w + x] = 0xFFFFFFFF;
	y = doom->c.y + 10 + 1;
	while (--y > doom->c.y + 2)
		pixels[y * doom->surface->w + x] = 0xFFFFFFFF;
	y = doom->c.y;
	x = doom->c.x - 10 - 1;
	while (++x < doom->c.x - 2)
		pixels[y * doom->surface->w + x] = 0xFFFFFFFF;
	x = doom->c.x + 10 + 1;
	while (--x > doom->c.x + 2)
		pixels[y * doom->surface->w + x] = 0xFFFFFFFF;
	draw_hit_marker(doom);
}
