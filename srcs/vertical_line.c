/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 12:56:23 by nneronin          #+#    #+#             */
/*   Updated: 2020/10/27 17:35:22 by nneronin         ###   ########.fr       */
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

void	t_vline1(t_doom *doom, int x, t_ab y, t_ab cy)
{
	int	res		= (cy.a1 - y.a1) * WALL_TEXTURE_H / (y.b1 - y.a1);
	int	ca		= abs(y.b1 - y.a1);
	int	cache	= (int)((cy.a1 - y.a1) * WALL_TEXTURE_H) % abs(y.b1 - y.a1);
	int y1		= clamp(cy.a1, 0, H - 1);
	int y2		= clamp(cy.b1, 0, H - 1);

	while (y1++ <= y2)
    {
		cache += WALL_TEXTURE_H;
		while (cache >= ca)
		{
			res += 1;
			cache -= ca;
		}
		((int*)doom->surface->pixels)[y1 * W + x] =
			((int*)doom->txtx->pixels)[(res % IMG_RES) * IMG_RES + (doom->affine_x % IMG_RES)];
    }
}
