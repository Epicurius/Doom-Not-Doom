/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:52:00 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 17:06:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void		clamp_line(SDL_Surface *surf, Uint32 color, int x, int y)
{
	int pix;

	pix = (y * surf->w + x);
	if (pix > 0 && pix < (surf->w * surf->h))
    		((int*)surf->pixels)[pix] = color;
}

void	line(SDL_Surface *surf, Uint32 color, t_point *p)
{
	int			cath_x;
	int			cath_y;
	int			overflow_x;
	int			overflow_y;

	cath_x = abs(p[1].y - p[0].y);
	cath_y = abs(p[1].x - p[0].x);
	overflow_y = cath_y - cath_x;
	while (p[0].x != p[1].x || p[0].y != p[1].y)
	{
    		clamp_line(surf, color, p[0].x, p[0].y);
		overflow_x = overflow_y * 2;
		if (overflow_x > -(cath_x))
		{
			overflow_y -= cath_x;
			p[0].x += p[0].x < p[1].x ? 1 : -1;
		}
		else if (overflow_x < cath_x)
		{
			overflow_y += cath_y;
			p[0].y += p[0].y < p[1].y ? 1 : -1;
		}
	}
}
