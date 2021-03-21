
#include "doom.h"


void	draw_crosshair2(t_doom *doom)
{
	int		y;
	int		x;
	int		max;
	Uint32	*pixels;

	pixels = doom->surface->pixels;
	y = doom->h2;
	x = doom->w2 - 10;
	max = doom->w2 - 2;
	while (x < max)
	{
		pixels[x + y * W] = 0xFFFFFFFF;
		x++;
	}
	x = doom->w2 + 10;
	max = doom->w2 + 2;
	while (x > max)
	{
		pixels[x + y * W] = 0xFFFFFFFF;
		x--;
	}
}

void	draw_crosshair(t_doom *doom)
{
	int		y;
	int		x;
	int		max;
	Uint32	*pixels;

	pixels = doom->surface->pixels;;
	x = doom->w2;
	y = doom->h2 - 10;
	max = doom->h2 - 2;
	while (y < max)
	{
		pixels[x + y * W] = 0xFFFFFFFF;
		y++;
	}
	y = doom->h2 + 10;
	max = doom->h2 + 2;
	while (y > max)
	{
		pixels[x + y * W] = 0xFFFFFFFF;
		y--;
	}
	draw_crosshair2(doom);
}
