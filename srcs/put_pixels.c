/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:31 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 10:53:32 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_pixel_brightness(t_render *render, int coord, t_xyz text, t_bxpm *bxpm)
{
	unsigned short	light;
	unsigned short	pixel;

	light = 255 + render->light;
	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	((Uint32*)render->surface->pixels)[coord] = bxpm->palet[light][pixel];
	((double*)render->surface->userdata)[coord] = text.z;
}

void	blit_pixel_alpha(t_render *render, int coord, t_xyz text, t_bxpm *bxpm)
{
	unsigned short	pixel;
	uint8_t			alpha;

	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	alpha = (bxpm->clr[pixel] >> 24 & 0xFF);
	if (alpha == 0)
		return ;
	((uint32_t*)render->surface->pixels)[coord] = 
		blend_alpha(bxpm->clr[pixel], ((uint32_t*)render->surface->pixels)[coord], -alpha);
}

void	blit_pixel_opaque(t_render *render, int coord, t_xyz text, t_bxpm *bxpm)
{
	unsigned short	light;
	unsigned short	pixel;

	light = 255 + render->light;
	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	if (bxpm->clr[pixel] == 0xFF800080)
		return ;
	((uint32_t*)render->surface->pixels)[coord] = bxpm->clr[pixel];
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
