/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Copy pixel to surface and add light.
 */
void	blit_pixel_brightness(t_render *render, int coord, t_v3 text,
	t_bxpm *bxpm)
{
	unsigned short	pixel;

	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	((Uint32 *)render->surface->pixels)[coord]
		= bxpm->shade[render->light][pixel];
	((float *)render->surface->userdata)[coord] = text.z;
}

/*
 *	Copy pixel to surface if color is not 800080(pink/purple).
 */
void	blit_pixel_opaque(t_render *render, int coord, t_v3 text, t_bxpm *bxpm)
{
	unsigned short	pixel;

	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	if (bxpm->clr[pixel] == 0xFF800080)
		return ;
	((Uint32 *)render->surface->pixels)[coord] = bxpm->clr[pixel];
	((float *)render->surface->userdata)[coord] = text.z;
}

/*
 *	Copy pixel to surface.
 *	Specificity for skybox because it does not need to check zbuffer,
 *	just set it to render distance + 1.
 */
void	blit_pixel_skybox(t_render *render, int coord, t_v3 text, int side)
{
	t_bxpm			*bxpm;
	unsigned short	pixel;

	bxpm = &render->stx[side];
	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	((Uint32 *)render->surface->pixels)[coord] = bxpm->clr[pixel];
	((float *)render->surface->userdata)[coord] = RENDER_DISTANCE + 1;
}
