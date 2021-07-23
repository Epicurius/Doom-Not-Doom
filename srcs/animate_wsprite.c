/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_wsprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:28:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/21 11:03:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

//void	wsprite_action(t_doom *doom, t_wsprite *wsprite)
//{
//	if (wsprite->state == LOOP)
//		animate_wsprite(doom, wsprite);
//	else if (wsprite->state == CLICKING)
//	{
//		if (doom->player.action == CLICKING)
//			animate_wsprite(doom, wsprite);	
//	}
//	else if (wsprite->state == SHOOTINNG)
//	{
//		if (doom->player.action == SHOOTING)
//			animate_wsprite(doom, wsprite);	
//	}
//}
