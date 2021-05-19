/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit_bxpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 10:39:24 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/19 16:05:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_bxpm(SDL_Surface *surface, t_bxpm *bxpm, int sx, int sy)
{
	Uint32 clr;
	int x;
	int y;

	y = 0;
	while (y < bxpm->h)
	{
		x = 0;
		while (x < bxpm->w)
		{
			clr = bxpm->clr[bxpm->pix[y * bxpm->w + x]];
			if (clr != 0x000000)
				((Uint32*)surface->pixels)[(sy + y) * surface->w + (sx + x)] = clr;
			x++;
		}
		y++;
	}
}

static void		copy_pixel(SDL_Surface *dst, t_rect dstr, t_bxpm *src, t_rect srcr)
{
	uint32_t clr;

	clr = src->clr[src->pix[srcr.y2 * src->w + srcr.x2]];
	if (clr != 0x000000 && clr != 0xFFc10099)
		((Uint32*)dst->pixels)[dstr.y2 * dst->w + dstr.x2] = clr;
}

void		copy_column(SDL_Surface *dst, t_rect dstr, t_bxpm *src, t_rect srcr)
{
	int inc;
	int pos;

	pos = 0x10000;
	inc = (srcr.h << 16) / dstr.h;
	srcr.y2 = srcr.y1;
	dstr.y2 = dstr.y1;
	while (dstr.y2 < dstr.y1 + dstr.h)
	{
		while (pos >= 0x10000L)
		{
			srcr.y2++;
			pos -= 0x10000L;
		}
		if (dstr.y2 > 0 && dstr.y2 < dst->h - 1)
			copy_pixel(dst, dstr, src, srcr);
		pos += inc;
		dstr.y2++;
	}
}

void	blit_bxpm_scaled(SDL_Surface *dst, t_rect dstr, t_bxpm *src, t_rect srcr)
{
	int pos;
	int inc;
	
	pos = 0x10000;
	inc = (srcr.w << 16) / dstr.w;
	srcr.x2 = srcr.x1;
	dstr.x2 = dstr.x1;
	while (dstr.x2 < dstr.x1 + dstr.w)
	{
		while (pos >= 0x10000L)
		{
			srcr.x2++;
			pos -= 0x10000L;
		}
		if (dstr.x2 > 0 && dstr.x2 < dst->w - 1)
			copy_column(dst, dstr, src, srcr);
		pos += inc;
		dstr.x2++;
	}
}
