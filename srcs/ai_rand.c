/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:42:13 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/01 16:50:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	ai_rand_move(t_game_entity *entity, int rand)
{
	double angle;

	if (rand > 360 || rand < 0)
		return (0);
	angle = rand * CONVERT_RADIANS;
	entity->dest.x = (entity->data->wonder_distance * cos(angle));
	entity->dest.y = (entity->data->wonder_distance * sin(angle));
	entity->dest.x += entity->where.x;
	entity->dest.y += entity->where.y;
	entity->dest.z = entity->where.z;
	return (1);
}
