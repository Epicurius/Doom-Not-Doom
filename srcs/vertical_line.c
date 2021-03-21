/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/19 12:56:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		shade_hex_color(int color, float shade_factor)
{
	SDL_Color c;

	c.a = (color >> 24) & 0xFF;
	c.r = (color >> 16) & 0xFF;
	c.g = (color >> 8) & 0xFF;
	c.b = (color) & 0xFF;
	c.r = c.r * shade_factor;
	c.g = c.g * shade_factor;
	c.b = c.b * shade_factor;
	return ((c.r & 0xFF) << 16 | (c.g & 0xFF) << 8 | (c.b & 0xFF) | (c.a & 0xFF) << 24);
}

void	vline_color(t_render *render, t_vline *vline, int c)
{
	int	x;
	int	y;
	int	y1;
	int	y2;
	Uint32	*pix;

	x = render->x;
	//color = shade_hex_color(c, render->light); 
	pix = (Uint32*)render->surface->pixels;
	y1 = clamp(vline->y1, 0, render->surface->h);
	y2 = clamp(vline->y2, 0, render->surface->h);
	if (y1 < y2)
	{
        	pix[y1 * render->surface->w + x] = 0xFF000000;
		y = y1 + 1;
		while (y < y2)
		{
			pix[y * render->surface->w + x] = c;
			y++;
		}
		pix[y2 * render->surface->w + x] = 0xFF000000;
	}
}
/*
int		doom_pixel_copy(t_render *render, int pixel, int dst_add)
{
	if (((char*)render->surface->userdata)[dst_add] > 0)
		return (1);
	if (render->light < 1.0)
		((int*)render->surface->pixels)[dst_add] = 
			shade_hex_color(pixel, render->light);
	else
		((int*)render->surface->pixels)[dst_add] =
			pixel;
	//((char*)render->surface->userdata)[dst_add] = 127; //fix
	return (0);
}*/
