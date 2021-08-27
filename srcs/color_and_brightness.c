/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_brightness.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:32 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/27 10:51:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Converts Hexadeciaml color to SDL_Color (aka ARGB).
 */
SDL_Color	hex_to_sdl_color(int hex)
{
	SDL_Color	color;

	color.a = hex >> 24;
	color.r = hex >> 16;
	color.g = hex >> 8;
	color.b = hex;
	return (color);
}

/*
 * Darkens or brightens a color 
 * -x darker, 0 nothing, +x lighter obvs -255 to 255
 */
Uint32	brightness(Uint32 src, int light)
{
	if (light == 0)
		return (src);
	return (
		(int)ft_clamp(((light + 256) * (src >> 16 & 0xFF)) / 256, 0, 255) << 16
		| (int)ft_clamp(((light + 256) * (src >> 8 & 0xFF)) / 256, 0, 255) << 8
		| (int)ft_clamp(((light + 256) * (src & 0xFF)) / 256, 0, 255));
}

/*
 * Blends a src color with an alpha 0 - 255
 */
int	blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha)
{
	int	a;

	a = 256 - alpha;
	return (
		((a * (src >> 16 & 0xFF) + alpha * (dest >> 16 & 0xFF)) / 256) << 16
		| ((a * (src >> 8 & 0xFF) + alpha * (dest >> 8 & 0xFF)) / 256) << 8
		| ((a * (src & 0xFF) + alpha * (dest & 0xFF)) / 256));
}

/*
 *	Creates a separete palet of the BXPM image with the light shade.
 *	Saves it to bxpm->palet[light from -255 -> 255].
 */
void	shade_palet(t_bxpm *bxpm, int light)
{
	int	i;

	i = -1;
	if (bxpm->palet[255 + light])
		return ;
	bxpm->palet[255 + light] = protalloc(sizeof(Uint32 *) * bxpm->clr_nb,
			"color_palet");
	if (!bxpm->palet[255 + light])
		error_msg("bxpm->palet malloc");
	while (++i < bxpm->clr_nb)
	{
		if (bxpm->clr[i] == 0xFF800080)
			bxpm->palet[255 + light][i] = 0xFF800080;
		bxpm->palet[255 + light][i] = brightness(bxpm->clr[i], light);
	}
}

/*
 *	Check all the sectors light levels and textures, if a textures does not
 *	have the light palet then it creates one.
 */
void	shade_palets(t_doom *doom)
{
	int			s;
	int			w;
	t_sector	*sector;

	s = -1;
	while (++s < doom->nb.sectors)
	{
		w = -1;
		sector = &doom->sectors[s];
		while (++w < doom->sectors[s].npoints)
		{
			if (sector->wall[w]->wtx >= 0)
				shade_palet(&doom->mtx[sector->wall[w]->wtx], sector->light);
		}
		if (sector->ceiling.tx >= 0)
			shade_palet(&doom->mtx[sector->floor.tx], sector->light);
		if (sector->ceiling.tx >= 0)
			shade_palet(&doom->mtx[sector->ceiling.tx], sector->light);
	}
	s = -1;
	while (++s < doom->nb.events)
	{
		if (doom->events[s].type != LIGHT)
			continue ;
		w = -1;
		while (++w < doom->events[s].event_sector->npoints)
			shade_palet(&doom->mtx[doom->events[s].event_sector->wall[w]->wtx], doom->events[s].light);
		shade_palet(&doom->mtx[doom->events[s].event_sector->floor.tx], doom->events[s].light);
		shade_palet(&doom->mtx[doom->events[s].event_sector->ceiling.tx], doom->events[s].light);
	}
}
