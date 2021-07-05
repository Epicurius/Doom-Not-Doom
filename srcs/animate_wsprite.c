/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_wsprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:28:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/05 14:34:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	animate_wsprite(t_doom *doom, t_wsprite *sprite)
{
	if (sprite->time - doom->time.curr < -100)
	{
		sprite->src.x1 += 64;
		sprite->frame += 1;
		if (sprite->src.x1 >= doom->mtx[sprite->tx].w)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 += 64;
		}
		if (sprite->frame >= 3 || sprite->src.y1 >= doom->mtx[sprite->tx].h)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 = 0;
			sprite->frame = 0;
		}
		sprite->src.x2 = sprite->src.x1 + 64;
		sprite->src.y2 = sprite->src.y1 + 64;
		sprite->time = doom->time.curr;
	}
	return (1);
}
