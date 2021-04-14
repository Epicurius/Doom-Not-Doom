
#include "doom.h"

void	put_entity_pixel(t_entity_render *render, int coord, t_xyz text)
{
	Uint32		pixel;

	if (((double*)render->surface->userdata)[coord] < text.z)
		return ;
	pixel = ((Uint32*)render->texture->pixels)
		[(int)text.y * render->texture->w + (int)text.x];
	if (pixel == 0xFF800080)
		return ;
	((Uint32*)render->surface->pixels)[coord] = pixel;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_entity_pixel(t_entity_render *render, int coord, t_xyz text)
{
	uint32_t	clr;
	unsigned short	pix;

	if (text.z >= ((double*)render->surface->userdata)[coord])
		return ;
	pix = render->bxpm->pix[(int)text.y * render->bxpm->w + (int)text.x];
	clr = render->bxpm->clr[pix];
	if (clr == 0x800080)
		return ;
	((Uint32*)render->surface->pixels)[coord] = clr;
	((double*)render->surface->userdata)[coord] = text.z;
}
void	blit_entity(t_entity_render *render)
{
	t_v2 alpha;
	t_xyz text;

	text.z = render->screen.z;
	int y = render->clamp_start.y;
	while (++y < render->clamp_end.y)
	{
		alpha.y = (y - render->start.y) / render->yrange;
		text.y = (1.0 - alpha.y) * render->img.y1 + alpha.y * render->img.y2;
		int x = render->clamp_start.x;
		while (++x < render->clamp_end.x)
		{
			alpha.x = (x - render->start.x) / render->xrange;
			text.x = (1.0 - alpha.x) * render->img.x1 + alpha.x * render->img.x2;
			blit_entity_pixel(render, y * W + x, text);
		}
	}
}
