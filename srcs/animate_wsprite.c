/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Handels the wsprite frames, depending on game ticks.
 */
int	animate_wsprite(t_doom *doom, t_wsprite *wsprite)
{
	if (doom->time.curr - wsprite->time > WALL_SPRITE_SPEED)
	{
		wsprite->src.x1 += 64;
		wsprite->frame += 1;
		if (wsprite->src.x1 >= doom->mtx[wsprite->tx].w)
		{
			wsprite->src.x1 = 0;
			wsprite->src.y1 += 64;
		}
		if (wsprite->src.y1 >= doom->mtx[wsprite->tx].h)
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
