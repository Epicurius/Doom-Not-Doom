
#include "doom.h"

void	put_ceiling_pixels(t_render *render, int coord, t_xyz text)
{
	Uint32		*pixels;

	pixels = render->ctx->surface->pixels;
	((Uint32*)render->surface->pixels)[coord] = 
	brightness(pixels[(int)text.y * render->ctx->w + (int)text.x], render->light);
	((double*)render->surface->userdata)[coord] = text.z;
}

void	draw_ceiling_texture(t_render *render, t_vline *vline)
{
	t_xyz text;
	double alpha;
	double divider;
	int	coord;

	while (vline->y1 < vline->y2)
	{
		coord = vline->y1 * W + render->x;
		alpha = (vline->max.ceiling - vline->y1) / vline->height.ceiling;
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
		text.y *= render->ceiling.scale;
		text.x *= render->ceiling.scale;
		//text.x = render->ctx->w - text.x;
		if (text.y >= render->ctx->h || text.y < 0)
			text.y = abs((int)text.y % render->ctx->h);
		if (text.x >= render->ctx->w || text.x < 0)
			text.x = abs((int)text.x % render->ctx->w);
		put_ceiling_pixels(render, coord, text);
		vline->y1++;
	}
}
