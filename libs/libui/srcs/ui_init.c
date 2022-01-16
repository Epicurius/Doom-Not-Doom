/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:06 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/11 15:12:19 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

/*
 * The init of all the sdl stuff that libui needs.
*/
void	ui_sdl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
}

/*
 * The free of all the sdl stuff that libui needs.
*/
void	ui_sdl_free(void)
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
