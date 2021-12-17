/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:53:31 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/17 12:54:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 *	Copy pixel to surface if Alpha is not 0.
 */
void	blit_pixel_alpha(t_render *render, int coord, t_v3 text, t_bxpm *bxpm)
{
	unsigned short	pixel;
	uint8_t			alpha;

	pixel = bxpm->pix[(int)text.y * bxpm->w + (int)text.x];
	alpha = (bxpm->clr[pixel] >> 24 & 0xFF);
	if (alpha == 0)
		return ;
	((Uint32 *)render->surface->pixels)[coord] = blend_alpha(bxpm->clr[pixel],
			((Uint32 *)render->surface->pixels)[coord], -alpha);
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
	if ((floor(text.y) * bxpm->w + floor(text.x)) > bxpm->pix_nb)
	{
		ft_printf("1: %d %d\n", (int)floor(text.y) * bxpm->w + (int)floor(text.x), bxpm->pix_nb);
		exit (1);
	}	
	pixel = bxpm->pix[(int)floor(text.y) * bxpm->w + (int)floor(text.x)];
	if (pixel >= bxpm->clr_nb)
	{
		ft_printf("2\n");
		exit (1);
	}
	((Uint32 *)render->surface->pixels)[coord] = bxpm->clr[pixel];
	((float *)render->surface->userdata)[coord] = RENDER_DISTANCE + 1;
}
