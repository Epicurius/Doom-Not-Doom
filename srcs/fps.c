/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 10:58:35 by nneronin          #+#    #+#             */
/*   Updated: 2020/11/17 12:20:41 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void				fps_func(t_doom *doom)
{
	char		*str;
	SDL_Rect	rect;
	SDL_Color	color;
	SDL_Surface *text;


	color = (SDL_Color){.r = 0, .g = 75, .b = 255, .a = 100};
	FPS.prev = FPS.curr;
	FPS.curr = SDL_GetTicks();
	FPS.avg = (FPS.curr - FPS.prev) * 1e-3;
	str = ft_itoa(1.0 / FPS.avg);
	if (!(text = TTF_RenderText_Solid(FPS.font, str, color)))
		printf("TTF_RenderText_Solid: %s\n", str);
	rect = (SDL_Rect){.x = 0, .y = 0, .w = text->w, .h = text->h};
	SDL_BlitSurface(text, NULL, doom->surface, &rect);
	SDL_FreeSurface(text);
	free(str);
}
