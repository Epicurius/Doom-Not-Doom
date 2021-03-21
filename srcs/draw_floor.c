
#include "doom.h"

void	put_floor_pixels(t_render *render, int coord, t_xyz text)
{
	Uint32		*pixels;

	pixels = render->ftx->surface->pixels;
	((int*)render->surface->pixels)[coord] =
	brightness(pixels[(int)text.y * render->ftx->w + (int)text.x], render->light); 
	((double*)render->surface->userdata)[coord] = text.z;
}

void	draw_floor_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	double divider;
	int coord;

	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->y1 - vline->max.floor) / vline->height.floor;
		divider = 1 / (NEAR_Z + alpha * vline->zrange);
		text.z = vline->z_near_z * divider;
		if (text.z >= ((double*)render->surface->userdata)[coord])
		{
			vline->y1++;
			continue;
		}
		text.y = (vline->texel_nearz.y + alpha * vline->texel_range.y)
				* divider;
		text.x = (vline->texel_nearz.x + alpha * vline->texel_range.x)
				* divider;
		text.y *= render->floor.scale;
		text.x *= render->floor.scale;
		
		//text.y = render->ftx->h - (text.y * render->floor.scale);
		//text.x = render->ftx->w - (text.x * render->floor.scale);
		if (text.y >= render->ftx->h || text.y < 0)
			text.y = abs((int)text.y % render->ftx->h);
		if (text.x >= render->ftx->w || text.x < 0)
			text.x = abs((int)text.x % render->ftx->w);
		put_floor_pixels(render, coord, text);
		vline->y1++;
	}
}
