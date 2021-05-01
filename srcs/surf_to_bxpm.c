/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surf_to_bxpm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:20:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/01 15:30:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

unsigned short	check_clr(t_bxpm *bxpm, uint32_t clr)
{
	unsigned short	i;

	i = -1;
	while (++i < bxpm->clr_nb)
	{
		if (bxpm->clr[i] == clr)
			return (i);
	}
	bxpm->clr_nb += 1;
	bxpm->clr = realloc(bxpm->clr, sizeof(uint32_t) * (bxpm->clr_nb));
	bxpm->clr[bxpm->clr_nb - 1] = clr;
	return (bxpm->clr_nb - 1);
}

void	surf_to_bxpm(SDL_Surface *surf, t_bxpm *bxpm)
{
	int i;

	bxpm->w = surf->w;
	bxpm->h = surf->h;
	bxpm->bpp = surf->format->BitsPerPixel;
	bxpm->clr_nb = 0;
	bxpm->pix_nb = surf->w * surf->h;
	bxpm->clr = malloc(sizeof(uint32_t));
	bxpm->pix = malloc(sizeof(unsigned short) * bxpm->pix_nb);
	i = -1;
	while (++i < bxpm->pix_nb)
	{
		bxpm->pix[i] = check_clr(bxpm, ((Uint32*)surf->pixels)[i]);
	}
	//printf("%d %d %d\n", bxpm->clr_nb, bxpm->pix_nb, bxpm->bpp);
}
