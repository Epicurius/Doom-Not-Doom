/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:42:13 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/21 11:19:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	ai_rand_move(t_entity *entity, int chance, int angle)
{
	double a;
	if ((rand() % 1000) > chance)
		return (0);
	a = (entity->angle + ((rand() % angle) - angle / 2)) * CONVERT_RADIANS;
	entity->dest.x = (100 * cos(a));
	entity->dest.y = (100 * sin(a));
	entity->dest.x += entity->where.x;
	entity->dest.y += entity->where.y;
	entity->dest.z = entity->where.z;
	return (1);
}
