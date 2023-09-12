/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Check it the player can stand up at its current pos.
 *	If player hits ceiling.
 *	If player is < 1.0 from neighbour wall and hits neighbour ceiling.
 */
int	crouch_collision(t_doom *doom, t_player *player)
{
	int		i;
	t_v3	point;
	t_wall	*wall;

	if (player->where.z + PLAYER_HEIGHT
		>= ceiling_at(&doom->sectors[player->sector], player->where))
		return (1);
	i = -1;
	while (++i < doom->sectors[player->sector].npoints)
	{
		wall = doom->sectors[player->sector].wall[i];
		if (wall->solid || wall->n == -1)
			continue ;
		point = closest_point_on_segment_v2(player->where, wall->v1, wall->v2);
		if (point_distance_v2(point.x, point.y,
				player->where.x, player->where.y) > DIAMETER)
			continue ;
		if (player->where.z + PLAYER_HEIGHT
			>= ceiling_at(&doom->sectors[wall->n], point))
			return (1);
	}
	return (0);
}
