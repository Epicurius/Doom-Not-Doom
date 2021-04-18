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

void	vline_color(t_render *render, t_vline *vline, int c)
{
	int	x;
	int	y;
	int	y1;
	int	y2;
	Uint32	*pix;

	x = render->x;
	pix = (Uint32*)render->surface->pixels;
	y1 = ft_clamp(vline->y1, 0, render->surface->h);
	y2 = ft_clamp(vline->y2, 0, render->surface->h);
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
