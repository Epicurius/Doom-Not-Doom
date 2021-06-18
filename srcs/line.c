/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:00 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/18 10:48:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline int	sign(int a, int b)
{
	if (a < b)
		return (1);
	return (-1);
}

static inline void	clamp_line(SDL_Surface *surf, Uint32 color, int x, int y)
{
	int	pix;

	pix = (y * surf->w + x);
	if (pix > 0 && pix < (surf->w * surf->h))
		((int *)surf->pixels)[pix] = color;
}

void	line(SDL_Surface *surf, Uint32 color, t_point *p)
{
	t_point		cath;
	t_point		overflow;

	cath.x = abs(p[1].y - p[0].y);
	cath.y = abs(p[1].x - p[0].x);
	overflow.y = cath.y - cath.x;
	while (p[0].x != p[1].x || p[0].y != p[1].y)
	{
		clamp_line(surf, color, p[0].x, p[0].y);
		overflow.x = overflow.y * 2;
		if (overflow.x > -(cath.x))
		{
			overflow.y -= cath.x;
			p[0].x += sign(p[0].x, p[1].x);
		}
		else if (overflow.x < cath.x)
		{
			overflow.y += cath.y;
			p[0].y += sign(p[0].y, p[1].y);
		}
	}
}
