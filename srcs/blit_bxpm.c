/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_bxpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:39:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/30 17:29:42 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	SDL_BlitSurface but from BXPM.
 *	Copies the BXPM to surface 1:1.
 */
void	blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm, int sx, int sy)
{
	int				x;
	int				y;
	Uint32			clr;
	Uint32			*dst;
	unsigned short	*pix;

	pix = bxpm->pix;
	dst = &((Uint32 *)surface->pixels)[sy * surface->w + sx];
	y = -1;
	while (++y < bxpm->h)
	{
		x = -1;
		while (++x < bxpm->w)
		{
			clr = bxpm->clr[pix[x]];
			if ((clr >> 24 & 0xFF) != 0)
				dst[x] = clr;
		}
		pix += bxpm->w;
		dst += surface->w;
	}
}
