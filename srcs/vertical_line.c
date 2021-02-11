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
	int hex;
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

void	vline1(t_render *render, int y1, int y2, int c)
{
	int	x;
	int	y;
	int	*pix;
	int	color;

	x = render->x;
	color = shade_hex_color(c, render->light); 
	pix = (int*)render->surface->pixels;
	y1 = clamp(y1, 0, H);
	y2 = clamp(y2, 0, H);
	if (y1 < y2)
	{
        	pix[y1 * W + x] = 0xFF000000;
		y = y1 + 1;
		while (y < y2)
		{
			pix[y * W + x] = color;
			y++;
		}
		pix[y2 * W + x] = 0xFF000000;
	}
}

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
	((char*)render->surface->userdata)[dst_add] = 1;
	return (0);
}

int		t_vline3(t_render *render, t_ab y, t_ab cy)
{
	int y1			= clamp(cy.a1, 0, H);
	int y2			= clamp(cy.b1, 0, H);
	if (y1 >= y2)
		return (0);
	int t_hight		= (render->height_info.yceil - render->height_info.yfloor) * (WTX_W / 12.8); //4
	int curr_y		= (cy.a1 - y.a1) * t_hight / (y.b1 - y.a1);	//texture y
	int dist_y		= abs(y.b1 - y.a1);	//Hight of strip
	int	total_y		= (int)((cy.a1 - y.a1) * t_hight) % abs(y.b1 - y.a1);//

	while (y1 < y2)
	{
		total_y += t_hight;
		int n = (total_y / dist_y);
		total_y -= dist_y * n;
		curr_y += n;
		doom_pixel_copy(render,
			((int*)render->wtx->pixels)[(curr_y % WTX_W) * WTX_W + (render->affine_x % WTX_W)],
			y1 * W + render->x);
		/*if (render->light < 1.0)
			((int*)render->surface->pixels)[y1 * W + render->x] = 
				shade_hex_color(((int*)render->wtx->pixels)[
					(curr_y % WTX_W) * WTX_W + (render->affine_x % WTX_W)], render->light);
		else
			((int*)render->surface->pixels)[y1 * W + render->x] =
				((int*)render->wtx->pixels)[(curr_y % WTX_W) *
					WTX_W + (render->affine_x % WTX_W)];*/
		y1 += 1;
    }
	return (0);
}
