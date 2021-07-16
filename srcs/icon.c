/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icon.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:29:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/16 20:35:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
