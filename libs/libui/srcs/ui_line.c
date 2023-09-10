/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * Line algorithm yoinked from:
 * http://elynxsdk.free.fr/ext-docs/Rasterization/Lines/Lines%20algorithms.htm
 * http://www.edepot.com/lined.html
*/
/*
void	ui_surface_line_draw_non_norme(
		SDL_Surface *surface, t_vec2i p1, t_vec2i p2, Uint32 color)
{
	bool	y_longer;
	int		increment_val;
	int		end_val;
	float	short_len;
	float	long_len;
	float	dec_inc;
	float	j;
	int		i;

	y_longer = false;
	short_len = p2.y - p1.y;
	long_len = p2.x - p1.x;
	y_longer = fabsf(short_len) > fabsf(long_len);
	if (y_longer)
		ft_fswap(&short_len, &long_len);
	end_val = long_len;
	increment_val = 1;
	if (long_len < 0)
	{
		increment_val = -1;
		long_len = -long_len;
	}
	dec_inc = 0;
	if (long_len != 0)
		dec_inc = short_len / long_len;
	j = 0;
	i = 0;
	if (y_longer)
	{
		while (i != end_val)
		{
			ui_surface_pixel_set(surface, p1.x + j, p1.y + i, color);
			j += dec_inc;
			i += increment_val;
		}
		return ;
	}
	while (i != end_val)
	{
		ui_surface_pixel_set(surface, p1.x + i, p1.y + j, color);
		j += dec_inc;
		i += increment_val;
	}
}
*/

static inline void	helperson(
	t_vec2 *short_long, t_vec2i *inc_end, float *dec_inc)
{
	inc_end->y = short_long->y;
	inc_end->x = 1;
	if (short_long->y < 0)
	{
		inc_end->x = -1;
		short_long->y = -short_long->y;
	}
	*dec_inc = 0;
	if (short_long->y != 0)
		*dec_inc = short_long->x / short_long->y;
}

static inline void	drawelson_yshorter(
	SDL_Surface *surface, t_vec2i p, t_vec2i inc_end, float dec_inc)
{
	float	j;
	int		i;
	Uint32	*color;

	j = 0;
	i = 0;
	color = surface->userdata;
	while (i != inc_end.y)
	{
		ui_surface_pixel_set(surface, p.x + i, p.y + j, *color);
		j += dec_inc;
		i += inc_end.x;
	}
}

static inline void	drawelson_ylonger(
	SDL_Surface *surface, t_vec2i p, t_vec2i inc_end, float dec_inc)
{
	float	j;
	int		i;
	Uint32	*color;

	j = 0;
	i = 0;
	color = surface->userdata;
	while (i != inc_end.y)
	{
		ui_surface_pixel_set(surface, p.x + j, p.y + i, *color);
		j += dec_inc;
		i += inc_end.x;
	}
}

/*
 * t_vec2 short_long; x == short_len, y == long_len;
 * t_vec2i inc_end; x == increment_val, y == end_val;
*/
void	ui_surface_line_draw(
		SDL_Surface *surface, t_vec2i p1, t_vec2i p2, Uint32 color)
{
	bool	y_longer;
	float	dec_inc;
	t_vec2	short_long;
	t_vec2i	inc_end;

	y_longer = false;
	short_long.x = p2.y - p1.y;
	short_long.y = p2.x - p1.x;
	y_longer = fabsf(short_long.x) > fabsf(short_long.y);
	surface->userdata = &color;
	if (y_longer)
	{
		ft_fswap(&short_long.x, &short_long.y);
		helperson(&short_long, &inc_end, &dec_inc);
		drawelson_ylonger(surface, p1, inc_end, dec_inc);
		return ;
	}
	helperson(&short_long, &inc_end, &dec_inc);
	drawelson_yshorter(surface, p1, inc_end, dec_inc);
}
