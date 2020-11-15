/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:51:07 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/15 19:01:59 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rearrange_corners(t_xyz *a, t_xyz *b, t_xyz *c)
{
	t_xyz tmp;

	if (a->y > b->y || (a->y == b->y && a->x > b->x))
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	if (a->y > c->y || (a->y == c->y && a->x > c->x))
	{
		tmp = *c;
		*c = *a;
		*a = tmp;
	}
	if (b->y > c->y || (b->y == c->y && b->x > c->x))
	{
		tmp = *b;
		*b = *c;
		*c = tmp;
	}
}

void	DrawScanline(SDL_Surface *surf, int y, int x1, int x2)
{
	while (x1 < x2)
		((int*)surf->pixels)[y * W + x1++] = 0xFF0000FF;
}

void trigon_rasterizer(SDL_Surface *surface, t_xyz a, t_xyz b, t_xyz c)	
{
	int sides[2];

	rearrange_corners(&a, &b, &c);
	if (a.y == c.y)
		printf("joynojyoonnoyjyoyjyomyojoy\n");
		//return ;

	int shortside = (b.y - a.y) * (c.x - a.x) < (b.x - a.x) * (c.y - a.y);
    if ((int)a.y < (int)b.y)
    {
        for (int y = a.y; y < (int)b.y; ++y)
		{
			sides[!shortside] = a.x + (float)((c.x - a.x) / (c.y - a.y)) * (y - a.y);
			sides[shortside] = a.x + (float)((b.x - a.x) / (b.y - a.y)) * (y - a.y);

            DrawScanline(surface, y, sides[0], sides[1]);
		}
    }
    if ((int)b.y < (int)c.y)
    {
        for (int y = b.y; y < (int)c.y; ++y)
		{
			sides[!shortside] = a.x + (float)((c.x - a.x) / (c.y - a.y)) * (y - a.y);
			sides[shortside] = b.x + (float)((c.x - b.x) / (c.y - b.y)) * (y - b.y);
            DrawScanline(surface, y, sides[0], sides[1]);
		}
    }
}
