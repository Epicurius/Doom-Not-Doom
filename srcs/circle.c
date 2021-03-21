
#include "doom.h"

void	draw_circle(SDL_Surface *surf, int color, t_ab ab)
{
    ((int*)surf->pixels)[(ab.a1 + ab.a2) * surf->w + (ab.b1 + ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.a2) * surf->w + (ab.b1 + ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 + ab.a2) * surf->w + (ab.b1 - ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.a2) * surf->w + (ab.b1 - ab.b2)] = color;
    ((int*)surf->pixels)[(ab.a1 + ab.b2) * surf->w + (ab.b1 + ab.a2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.b2) * surf->w + (ab.b1 + ab.a2)] = color;
    ((int*)surf->pixels)[(ab.a1 + ab.b2) * surf->w + (ab.b1 - ab.a2)] = color;
    ((int*)surf->pixels)[(ab.a1 - ab.b2) * surf->w + (ab.b1 - ab.a2)] = color;
}

void				circle(SDL_Surface *surf, Uint32 color, t_xyz xyz)
{
	t_ab ab;
	int dist;

	ab.a1 = xyz.y;
	ab.b1 = xyz.x;
	ab.a2 = 0;
	ab.b2 = xyz.z;
	dist = 3 - 2 * ab.b2;
	draw_circle(surf, color, ab);
	while (ab.b2 >= ab.a2)
	{
		ab.a2++;
		if (dist >= 0)
		{
			ab.b2--;
			dist = dist + 4 * (ab.a2 - ab.b2) + 10;
		}
		else
			dist = dist + 4 * ab.a2 + 6;
		draw_circle(surf, color, ab);
	}
}
