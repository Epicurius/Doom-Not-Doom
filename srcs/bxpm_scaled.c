
#include "doom.h"

/*
 *	Copies the y column.
 */
static inline void	copy_column(t_bxpm *dst, t_bxpm *src, int dy, int sy)
{
	int	inc;
	int	pos;
	int dx, sx;

	pos = 0x10000;
	inc = (src->w << 16) / dst->w;
	sx = 0;
	dx = 0;
	while (dx < dst->w)
	{
		while (pos > 0x10000L)
		{
			sx++;
			pos -= 0x10000L;
		}
		dst->pix[dy * dst->w + dx] = src->pix[sy * src->w + sx];
		pos += inc;
		dx++;
	}
}

/*
 *	SDL_BlitScaled but for BXPM.
 *	Blits the part from BXPM to part of the surface.
 *	Copies the x row.
 */
void	bxpm_scale(t_bxpm *dst, t_bxpm *src, int w, int h)
{
	int	pos;
	int	inc;
	int	dy, sy;

	dst->w = w;
	dst->h = h;
	dst->bpp = src->bpp;
	dst->pix_nb = dst->w * dst->h;
	dst->clr_nb = src->clr_nb;
	dst->pix = malloc(sizeof(unsigned short) * dst->pix_nb);
    dst->clr = src->clr;


	pos = 0x10000;
	inc = (src->h << 16) / dst->h;
	sy = 0;
	dy = 0;
	while (dy < dst->h)
	{
		while (pos > 0x10000L)
		{
			sy++;
			pos -= 0x10000L;
		}
		copy_column(dst, src, dy, sy);
		pos += inc;
		dy++;
	}
}