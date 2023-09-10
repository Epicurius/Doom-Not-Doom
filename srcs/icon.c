/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Set program icon.
 */
int	set_icon(SDL_Window *window, char *dir)
{
	SDL_Surface	*icon;

	icon = SDL_LoadBMP(dir);
	if (icon == NULL)
		return (0);
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
	return (1);
}
