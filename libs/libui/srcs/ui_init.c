/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

/*
 * The init of all the sdl stuff that libui needs.
*/
void	ui_sdl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
}

/*
 * The free of all the sdl stuff that libui needs.
*/
void	ui_sdl_free(void)
{
	TTF_Quit();
	SDL_Quit();
}
