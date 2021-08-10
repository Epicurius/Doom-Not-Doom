/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crouch_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:31:51 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/10 13:34:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
