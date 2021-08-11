/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_wsprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:28:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 08:58:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Handels the wsprite frames, depending on game ticks.
 */
int	animate_wsprite(t_doom *doom, t_wsprite *entity)
{
	if (entity->time - doom->time.curr < -100)
	{
		entity->src.x1 += 64;
		entity->frame += 1;
		if (entity->src.x1 >= doom->mtx[entity->tx].w)
		{
			entity->src.x1 = 0;
			entity->src.y1 += 64;
		}
		if (entity->frame >= 3 || entity->src.y1 >= doom->mtx[entity->tx].h)
		{
			entity->src.x1 = 0;
			entity->src.y1 = 0;
			entity->frame = 0;
		}
		entity->src.x2 = entity->src.x1 + 64;
		entity->src.y2 = entity->src.y1 + 64;
		entity->time = doom->time.curr;
	}
	return (1);
}
