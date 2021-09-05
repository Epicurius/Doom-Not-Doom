/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_circle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 14:41:28 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 06:51:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Blit pixels to surface if inside surface boundaries.
 */
static inline void	put_pixel(SDL_Surface *surface, Uint32 color, int x, int y)
{
	if (x > 0 && x < surface->w && y > 0 && y < surface->h)
		((Uint32 *)surface->pixels)[y * surface->w + x] = color;
}

/*
 *	Calculate the pixels positions from the center.
 */
static inline void	circle_points(SDL_Surface *surface, Uint32 color,
	t_point center, t_point c)
{
	put_pixel(surface, color, center.x - c.x, center.y - c.y);
	put_pixel(surface, color, center.x + c.x, center.y - c.y);
	put_pixel(surface, color, center.x - c.y, center.y - c.x);
	put_pixel(surface, color, center.x + c.y, center.y - c.x);
	put_pixel(surface, color, center.x - c.y, center.y + c.x);
	put_pixel(surface, color, center.x + c.y, center.y + c.x);
	put_pixel(surface, color, center.x - c.x, center.y + c.y);
	put_pixel(surface, color, center.x + c.x, center.y + c.y);
}

/*
 *	Draw a circle on surface with color on position with radius.
 */
void	draw_circle(SDL_Surface *surface, Uint32 color,
	t_point center, int size)
{
	int		dist;
	t_point	p;

	p.x = 0;
	p.y = size;
	dist = 3 - 2 * size;
	circle_points(surface, color, center, p);
	while (p.y >= p.x)
	{
		p.x++;
		if (dist >= 0)
		{
			p.y--;
			dist += 4 * (p.x - p.y) + 10;
		}
		else
			dist += 4 * p.x + 6;
		circle_points(surface, color, center, p);
	}
}
