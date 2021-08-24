/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_wsprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:28:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/24 14:45:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Handels the wsprite frames, depending on game ticks.
 */
int	animate_wsprite(t_doom *doom, t_wsprite *wsprite)
{
	if (doom->time.curr - wsprite->time > 100)
	{
		wsprite->src.x1 += 64;
		wsprite->frame += 1;
		if (wsprite->src.x1 >= doom->mtx[wsprite->tx].w)
		{
			wsprite->src.x1 = 0;
			wsprite->src.y1 += 64;
		}
		if (wsprite->frame >= 3 || wsprite->src.y1 >= doom->mtx[wsprite->tx].h) //fix
		{
			wsprite->src.x1 = 0;
			wsprite->src.y1 = 0;
			wsprite->frame = 0;
		}
		wsprite->src.x2 = wsprite->src.x1 + 64;
		wsprite->src.y2 = wsprite->src.y1 + 64;
		wsprite->time = doom->time.curr;
	}
	return (1);
}
