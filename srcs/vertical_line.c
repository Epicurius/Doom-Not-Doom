/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/09 20:14:22 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		rgb_to_hex(int r, int g, int b, int a)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF) | (a & 0xFF) << 24);
}

SDL_Color	hex_to_rgba(int rgba)
{
	SDL_Color color;
	
	color.a = (rgba >> 24) & 0xFF;
	color.r = (rgba >> 16) & 0xFF;
	color.g = (rgba >> 8) & 0xFF;
	color.b = (rgba) & 0xFF;
	return (color);
}

int		shade_hex_color(int color, float shade_factor)
{
	int hex;
	SDL_Color c;

	//if (!(shade_factor < 1.0))
	//	return (color);	
	c.a = (color >> 24) & 0xFF;
	c.r = (color >> 16) & 0xFF;
	c.g = (color >> 8) & 0xFF;
	c.b = (color) & 0xFF;
	c.r = c.r * (1 - shade_factor);
	c.g = c.g * (1 - shade_factor);
	c.b = c.b * (1 - shade_factor);
	//return ((c.r * 65536) + (c.g * 256) + c.b);	
	return ((c.r & 0xFF) << 16 | (c.g & 0xFF) << 8 | (c.b & 0xFF) | (c.a & 0xFF) << 24);
}

void	vline(t_doom *doom, int x, int y1, int y2)
{
	int	y;
    int	*pix;
	int middle;

	middle = 0xAAAAAA;
	if (x == SECTORS->viewpoint.x1 || x == SECTORS->viewpoint.x2)
			middle = 0;
	pix = (int*)doom->surface->pixels;
    y1 = clamp(y1, 0, H - 1);
    y2 = clamp(y2, 0, H - 1);
    if (y2 == y1)
        pix[y1 * W + x] = middle;
    else if (y2 > y1)
    {
        pix[y1 * W + x] = 0x0000FFFF;
		y = y1 + 1;
		while (y < y2)
		{
			pix[y * W + x] = middle;
			y++;
		}
        pix[y2 * W + x] = 0x0000FFFF;
    }
}

void	vline1(t_render *render, int y1, int y2, int c)
{
	int x;
	int	y;
    int	*pix;
	int	color;

	x = render->x;
	color = shade_hex_color(c, render->light); 
	pix = (int*)render->surface->pixels;
    y1 = clamp(y1, 0, H - 1);
    y2 = clamp(y2, 0, H - 1);
	if (y2 > y1)
    {
        pix[y1 * W + x] = color;
		y = y1 + 1;
		while (y < y2)
		{
			pix[y * W + x] = color;
			y++;
		}
		pix[y2 * W + x] = 0x000000;
    }
}

/*
void	t_vline1(t_doom *doom, int x, t_ab y, t_ab cy, float light)
{
	int hh		= (HEIGHT_INFO.yceil - HEIGHT_INFO.yfloor) * (IMG_RES / 12.8);// / 2;
	int	res		= (cy.a1 - y.a1) * hh / (y.b1 - y.a1);
	int	ca		= abs(y.b1 - y.a1);
	int	cache	= (int)((cy.a1 - y.a1) * hh) % abs(y.b1 - y.a1);
	int y1		= clamp(cy.a1, 0, H - 1);
	int y2		= clamp(cy.b1, 0, H - 1);

	while (y1++ <= y2)
    {
		cache += hh;
		while (cache >= ca)
		{
			res += 1;
			cache -= ca;
		}
		if (doom->light < 1.0)
			((int*)doom->surface->pixels)[y1 * W + x] = 
				shade_hex_color(((int*)doom->txtx->pixels)[
					(res % IMG_RES) * IMG_RES + (doom->affine_x % IMG_RES)], light);
		else
			((int*)doom->surface->pixels)[y1 * W + x] = ((int*)doom->txtx->pixels)[
					(res % IMG_RES) * IMG_RES + (doom->affine_x % IMG_RES)];
    }
}
int		t_vline2(void *arg)
{
	t_render	*render = arg;
	int hh		= (render->yceil - render->yfloor) * (render->img_res / 12.8);// / 2;
	int	res		= (render->cy.a1 - render->y.a1) * hh / (render->y.b1 - render->y.a1);
	int	ca		= abs(render->y.b1 - render->y.a1);
	int	cache	= (int)((render->cy.a1 - render->y.a1) * hh) % abs(render->y.b1 - render->y.a1);
	int y1		= clamp(render->cy.a1, 0, H - 1);
	int y2		= clamp(render->cy.b1, 0, H - 1);

	while (y1++ <= y2)
    {
		cache += hh;
		while (cache >= ca)
		{
			res += 1;
			cache -= ca;
		}
		if (render->light < 1.0)
			((int*)render->surface->pixels)[y1 * W + render->x] = 
				shade_hex_color(((int*)render->txtx->pixels)[
					(res % 64) * 64 + (render->affine_x % 64)], render->light);
		else
			((int*)render->surface->pixels)[y1 * W + render->x] = ((int*)render->txtx->pixels)[
					(res % 64) * 64 + (render->affine_x % 64)];
    }
	return (0);
}
*/
int		t_vline3(t_render *render, t_ab y, t_ab cy)
{
	int hh		= (render->height_info.yceil - render->height_info.yfloor) * (render->img_res / 12.8);// / 2;
	int	res		= (cy.a1 - y.a1) * hh / (y.b1 - y.a1);
	int	ca		= abs(y.b1 - y.a1);
	int	cache	= (int)((cy.a1 - y.a1) * hh) % abs(y.b1 - y.a1);
	int y1		= clamp(cy.a1, 0, H - 1);
	int y2		= clamp(cy.b1, 0, H - 1);

	while (y1++ <= y2)
    {
		cache += hh;
		while (cache >= ca)
		{
			res += 1;
			cache -= ca;
		}
		if (render->light < 1.0)
			((int*)render->surface->pixels)[y1 * W + render->x] = 
				shade_hex_color(((int*)render->txtx->pixels)[
					(res % 64) * 64 + (render->affine_x % 64)], render->light);
		else
			((int*)render->surface->pixels)[y1 * W + render->x] = ((int*)render->txtx->pixels)[
					(res % 64) * 64 + (render->affine_x % 64)];
    }
	return (0);
}
