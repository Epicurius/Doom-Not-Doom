/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icon.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 13:29:50 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/12 13:33:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_set_icon(SDL_Window *window, char *dir)
{
	SDL_Surface *icon;

	icon = SDL_LoadBMP(dir);
	if (icon == NULL)
		return ;
	SDL_SetWindowIcon(window, icon);
	SDL_FreeSurface(icon);
}
