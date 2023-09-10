/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

SDL_Rect	create_sdl_rect(int x, int y, int w, int h)
{
	return ((SDL_Rect){x, y, w, h});
}

SDL_Color	rgba_to_sdl_color(t_rgba rgba)
{
	SDL_Color	color;

	color.r = rgba.r;
	color.g = rgba.g;
	color.b = rgba.b;
	color.a = rgba.a;
	return (color);
}

t_rgba	hex_to_rgba(Uint32 color_hex)
{
	t_rgba	rgba;

	rgba.a = (color_hex >> 24 & 0xff);
	rgba.r = (color_hex >> 16 & 0xff);
	rgba.g = (color_hex >> 8 & 0xff);
	rgba.b = (color_hex & 0xff);
	return (rgba);
}

Uint32	rgba_to_hex(t_rgba rgba)
{
	return ((rgba.a & 0xff) << 24
		| ((rgba.r & 0xff) << 16)
		| ((rgba.g & 0xff) << 8)
		| (rgba.b & 0xff));
}

/*
 * Returns darkened version of the original color by procentage;
*/
Uint32	ui_color_change_brightness(Uint32 orig_col, float procentage)
{
	t_rgba	rgba;

	rgba = hex_to_rgba(orig_col);
	if (procentage < 0)
	{
		rgba.r = (255 - rgba.r) * procentage + rgba.r;
		rgba.g = (255 - rgba.g) * procentage + rgba.g;
		rgba.b = (255 - rgba.b) * procentage + rgba.b;
		return (rgba_to_hex(rgba));
	}
	procentage += 1;
	rgba.r *= procentage;
	rgba.g *= procentage;
	rgba.b *= procentage;
	return (rgba_to_hex(rgba));
}
