/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enetety_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:47:53 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/26 14:08:11 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int	error_check(SDL_Surface *src, SDL_Rect *sr, SDL_Surface *dst, SDL_Rect *dr)
{
        if (!sr || sr->x < 0 || sr->y < 0 ||
		(sr->x + sr->w) > src->w ||
		(sr->y + sr->h) > src->h)
		return (0);
        if (!dr || dr->x < 0 || dr->y < 0 ||
		(dr->x + dr->w) > dst->w ||
		(dr->y + dr->h) > dst->h)
    		return (0);
	return (1);
}

void		copy_pixel(SDL_Surface *src, SDL_Surface *dst, t_entity e, t_ab xy)
{
	int pixel;
	int dst_add;

	dst_add = xy.b2 * dst->w + xy.a2;
	if (((char*)dst->userdata)[dst_add] > 0)
		return ;
	pixel = ((int*)src->pixels)[xy.b1 * src->w + xy.a1];
	if (((pixel >> 24) & 0xFF) < OPAQUE)
		return ;
	((int*)dst->pixels)[dst_add] = pixel;
	((char*)dst->userdata)[dst_add] = e.id;
}

void		copy_column(SDL_Surface *src, SDL_Surface *dst, t_entity e, t_ab xy)
{
	int inc;
	int pos;

	pos = 0x10000;
	inc = (e.srcr.h << 16) / e.dstr.h;
	xy.b1 = e.srcr.y;
	xy.b2 = e.dstr.y;
	while (xy.b2 < e.dstr.y + e.dstr.h)
	{
		while (pos >= 0x10000L)
		{
			xy.b1++;
			pos -= 0x10000L;
		}
		if (xy.b2 > 0 && xy.b2 < dst->h)
			copy_pixel(src, dst, e, xy);
		pos += inc;
		xy.b2++;
	}
}


int	BlitScaled(SDL_Surface *src, SDL_Surface *dst, t_entity e)
{
	int pos;
	int inc;
	t_ab xy;
	
	pos = 0x10000;
	inc = (e.srcr.w << 16) / e.dstr.w;
	xy.a1 = e.srcr.x;
	xy.a2 = e.dstr.x;
	while (xy.a2 < e.dstr.x + e.dstr.w)
	{
		while (pos >= 0x10000L)
		{
			xy.a1++;
			pos -= 0x10000L;
		}
		if (xy.a2 > 0 && xy.a2 < dst->w)
			copy_column(src, dst, e, xy);
		pos += inc;
		xy.a2++;
	}
	return (1);
}
