/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	init_minimap(t_doom *doom)
{
	int		h;
	t_map	*map;

	map = &doom->map;
	h = doom->surface->h * (float)MM_SCALE;
	map->size = rect_xy2(doom->c.x - h / 2, doom->c.y - h / 2,
			doom->c.x + h / 2, doom->c.y + h / 2);
	map->pos.x = doom->c.x;
	map->pos.y = doom->c.y;
	map->zoom = MM_SECTORS_SCALE;
}
