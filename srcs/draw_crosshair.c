/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:43:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/25 10:35:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	draw_crosshair2(t_doom *doom)
{
	int		y;
	int		x;
	int		w;
	int		max;
	Uint32	*pixels;

	w = doom->surface->w;
	pixels = doom->surface->pixels;
	y = doom->c.y;
	x = doom->c.x - 10;
	max = doom->c.x - 2;
	while (x < max)
	{
		pixels[y * w + x] = 0xFFFFFFFF;
		x++;
	}
	x = doom->c.x + 10;
	max = doom->c.x + 2;
	while (x > max)
	{
		pixels[y * w + x] = 0xFFFFFFFF;
		x--;
	}
}

void	draw_crosshair(t_doom *doom)
{
	int		y;
	int		x;
	int		w;
	int		max;
	Uint32	*pixels;

	w = doom->surface->w;
	pixels = doom->surface->pixels;
	x = doom->c.x;
	y = doom->c.y - 10;
	max = doom->c.y - 2;
	while (y < max)
	{
		pixels[y * w + x] = 0xFFFFFFFF;
		y++;
	}
	y = doom->c.y + 10;
	max = doom->c.y + 2;
	while (y > max)
	{
		pixels[y * w + x] = 0xFFFFFFFF;
		y--;
	}
	draw_crosshair2(doom);
}
