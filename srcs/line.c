
#include "doom.h"

static inline void		clamp_line(SDL_Surface *surf, Uint32 color, int x, int y)
{
	int pix;

	pix = (y * surf->w + x);
	if (pix > 0 && pix < (surf->w * surf->h))
    		((int*)surf->pixels)[pix] = color;
}

void	line(SDL_Surface *surf, Uint32 color, t_i2 *p)
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

/*
void	ft_line(SDL_Surface *surf, int color, int x1, int y1, int x2, int y2)
{
	int			cath_x;
	int			cath_y;
	int			overflow_x;
	int			overflow_y;

	cath_x = abs(y2 - y1);
	cath_y = abs(x2 - x1);
	overflow_y = cath_y - cath_x;
	while (x1 != x2 || y1 != y2)
	{
    		clamp_line(surf, x1, y1, color);
		overflow_x = overflow_y * 2;
		if (overflow_x > -(cath_x))
		{
			overflow_y -= cath_x;
			x1 += x1 < x2 ? 1 : -1;
		}
		else if (overflow_x < cath_x)
		{
			overflow_y += cath_y;
			y1 += y1 < y2 ? 1 : -1;
		}
	}
}*/
