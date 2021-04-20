
#include "doom.h"

void	blit_pixel(t_render *render, int coord, t_xyz text, t_texture *tx)
{
	Uint32		*pixels;

	pixels = tx->surface->pixels;
	((Uint32*)render->surface->pixels)[coord] =
	pixels[(int)text.y * tx->w + (int)text.x];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_brightness(t_render *render, int coord, t_xyz text, t_bxpm *bxpm)
{
	unsigned short	light;
	unsigned short	pixel;

	light = 255 + render->light;
	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	((Uint32*)render->surface->pixels)[coord] = bxpm->palet[light][pixel];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_opaque(t_render *render, int coord, t_xyz text, t_bxpm *bxpm)
{
	unsigned short	light;
	unsigned short	pixel;

	light = 255 + render->light;
	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	if (bxpm->palet[light][pixel] == 0x800080)
			return ;
	((Uint32*)render->surface->pixels)[coord] = bxpm->palet[light][pixel];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_skybox(t_render *render, int coord, t_xyz text, int side)
{
	t_bxpm *bxpm;

	bxpm = &render->stx[side];
	((Uint32*)render->surface->pixels)[coord] =
		bxpm->clr[bxpm->pix[(int)text.y * bxpm->w + (int)text.x]];
	((double*)render->surface->userdata)[coord] = RENDER_DISTANCE + 1;
}
