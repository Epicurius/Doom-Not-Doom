/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:06 by jsalmi            #+#    #+#             */
/*   Updated: 2022/01/23 11:43:07 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
