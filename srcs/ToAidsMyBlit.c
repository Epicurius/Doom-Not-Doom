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

void		copy_column(int *src, SDL_Rect *sr, int *dst, SDL_Rect *dr)
{
	int i;
	int inc;
	int pixel = 0;
	int pos = 0x10000;

	i = -1;
	inc = (sr->h << 16) / dr->h;
	while (++i < dr->h)
	{
		while (pos >= 0x10000L)
		{
			pixel = *src;
			src += sr->w;
			pos -= 0x10000L;
		}
		if (!(((pixel >> 24) & 0xFF) < OPAQUE)) //Fixa
			*dst = pixel;
		dst += W;
		pos += inc;
	}
}

int	SoftStretch(SDL_Surface *src, SDL_Rect *sr, SDL_Surface *dst, SDL_Rect *dr)
{
	int pos;
	int inc;
	int src_x;
	int dst_x;
	int *src_start = NULL;
	int *dst_start;

        if (!sr || sr->x < 0 || sr->y < 0 ||
		(sr->x + sr->w) > src->w ||
		(sr->y + sr->h) > src->h)
		return (0);
        if (!dr || dr->x < 0 || dr->y < 0 ||
		(dr->x + dr->w) > dst->w ||
		(dr->y + dr->h) > dst->h)
    		return (0);
	pos = 0x10000;
	inc = (sr->w << 16) / dr->w;
	src_x = sr->x;
	dst_x = dr->x;
	while (dst_x < dr->x + dr->w)
	{
		dst_start = &((int*)dst->pixels)[dr->y * dst->w + dst_x];
		while (pos >= 0x10000L)
		{
			src_start = &((int*)src->pixels)[sr->y * src->w + src_x];
			src_x++;
			pos -= 0x10000L;
		}
		copy_column(src_start, sr, dst_start, dr);
		pos += inc;
		dst_x++;
	}
	return (1);
}

