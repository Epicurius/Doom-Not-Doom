
#include "doom.h"

//	precalc all texture brightness will save 10fps

void	blit_pixel(t_render *render, int coord, t_xyz text, t_texture *tx)
{
	Uint32		*pixels;

	pixels = tx->surface->pixels;
	((Uint32*)render->surface->pixels)[coord] =
	pixels[(int)text.y * tx->w + (int)text.x];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_brightness(t_render *render, int coord, t_xyz text, t_texture *tx)
{
	Uint32		*pixels;

	pixels = tx->surface->pixels;
	((Uint32*)render->surface->pixels)[coord] =
	brightness(pixels[(int)text.y * tx->w + (int)text.x], render->light);
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_opaque(t_render *render, int coord, t_xyz text, t_texture *tx)
{
	Uint32		pixel;

	pixel = ((Uint32*)tx->surface->pixels)[(int)text.y * tx->w + (int)text.x];
	if (((pixel >> 24) & 0xFF) < OPAQUE)
		return ;
	((Uint32*)render->surface->pixels)[coord] = pixel;
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_skybox(t_render *render, int coord, t_xyz text, int side)
{
	Uint32		*pixels;

	pixels = render->stx[side].surface->pixels;
	((Uint32*)render->surface->pixels)[coord] =
	pixels[(int)text.y * 2048 + (int)text.x];
	//brightness(pixels[(int)text.y * 2048 + (int)text.x], render->light);
}
