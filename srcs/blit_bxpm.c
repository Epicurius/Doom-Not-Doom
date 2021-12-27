/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_bxpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:39:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/27 16:09:53 by nneronin         ###   ########.fr       */
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

/*
 *	Copy pixel if its alpha is not 0.
 */
static void	copy_pixel(SDL_Surface *dst, t_rect dstr, t_bxpm *src, t_rect srcr)
{
	Uint32	clr;

	clr = src->clr[src->pix[srcr.y2 * src->w + srcr.x2]];
	if (0 != (clr >> 24 & 0xFF))
		((Uint32 *)dst->pixels)[dstr.y2 * dst->w + dstr.x2] = clr;
}

/*
 *	Copies the y column.
 */
static void	copy_column(SDL_Surface *dst, t_rect dstr, t_bxpm *src, t_rect srcr)
{
	int	inc;
	int	pos;

	pos = 0x10000;
	inc = (srcr.h << 16) / dstr.h;
	srcr.y2 = srcr.y1;
	dstr.y2 = dstr.y1;
	while (dstr.y2 < dstr.y1 + dstr.h)
	{
		while (pos > 0x10000L)
		{
			srcr.y2++;
			pos -= 0x10000L;
		}
		if (dstr.y2 > 0 && dstr.y2 < dst->h)
			copy_pixel(dst, dstr, src, srcr);
		pos += inc;
		dstr.y2++;
	}
}

/*
 *	SDL_BlitScaled but for BXPM.
 *	Blits the part from BXPM to part of the surface.
 *	Copies the x row.
 */
void	blit_bxpm_scaled(SDL_Surface *dst, t_rect dstr,
			t_bxpm *src, t_rect srcr)
{
	int	pos;
	int	inc;

	pos = 0x10000;
	inc = (srcr.w << 16) / dstr.w;
	srcr.x2 = srcr.x1;
	dstr.x2 = dstr.x1;
	while (dstr.x2 < dstr.x1 + dstr.w)
	{
		while (pos > 0x10000L)
		{
			srcr.x2++;
			pos -= 0x10000L;
		}
		if (dstr.x2 > 0 && dstr.x2 < dst->w)
			copy_column(dst, dstr, src, srcr);
		pos += inc;
		dstr.x2++;
	}
}
