/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/04 10:39:24 nneronin
 * Updated: 2022/01/03 18:03:48 nneronin
 */

#include "doom.h"

/*
 *	SDL_BlitSurface but from BXPM.
 *	Copies the z amount BXPM to surface.
 */
void	blit_bxpm2(t_weapon_thread *thread,
	SDL_Surface *surface, t_bxpm *bxpm)
{
	int				x;
	int				y;
	Uint32			clr;
	Uint32			*dst;
	unsigned short	*pix;

	pix = &bxpm->pix[thread->sy1 * bxpm->w + thread->sx1];
	dst = &((Uint32 *)surface->pixels)[thread->dy1 * surface->w + thread->dx1];
	y = thread->sy1;
	while (y < thread->sy2)
	{
		x = thread->sx1;
		while (x < thread->sx2)
		{
			clr = bxpm->clr[pix[x]];
			if ((clr >> 24 & 0xFF) != 0)
				dst[x - thread->sx1] = clr;
			x++;
		}
		y++;
		pix += bxpm->w;
		dst += surface->w;
	}
}

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

	pix = &bxpm->pix[0];
	dst = &((Uint32 *)surface->pixels)[sy * surface->w + sx - 1];
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
