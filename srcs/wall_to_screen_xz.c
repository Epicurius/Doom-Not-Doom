/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Translate map (x,y) coordinates to screen (x,z) coordinates.
 */
void	map_to_screen_vertex(t_player player, t_v3 *map, t_v3 *screen)
{
	t_v2	v;

	v.x = map->x - player.where.x;
	v.y = map->y - player.where.y;
	screen->x = v.x * player.anglesin - v.y * player.anglecos;
	screen->z = v.x * player.anglecos + v.y * player.anglesin;
}

/*
 *	Translate screen (x,z) coordinates to map (x,y) coordinates.
 */
void	screen_to_map_vertex(t_player player, t_v3 *screen, t_v3 *map)
{
	map->x = screen->x * player.anglesin + screen->z * player.anglecos;
	map->y = screen->z * player.anglesin - screen->x * player.anglecos;
	map->x += player.where.x;
	map->y += player.where.y;
}
