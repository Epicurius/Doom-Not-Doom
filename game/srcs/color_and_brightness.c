/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Converts Hexadecimal color to SDL_Color (aka ARGB).
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
 * -x darker, 0 nothing, +x lighter 0 - 512 (-255 to 255)
 */
Uint32	brightness(Uint32 src, int light)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = ft_min((src >> 16 & 0xFF) * light / 100, 255);
	g = ft_min((src >> 8 & 0xFF) * light / 100, 255);
	b = ft_min((src & 0xFF) * light / 100, 255);
	return (255 << 24 | r << 16 | g << 8 | b);
}

/*
 * Blends a src colors
 */
unsigned int	blend_colors(unsigned int src, unsigned int dest)
{
	return (255 << 24
		| (((256 - (dest >> 24 & 0xFF)) * (src >> 16 & 0xFF)
				+ (dest >> 24 & 0xFF) * (dest >> 16 & 0xFF)) / 256) << 16
		| (((256 - (dest >> 24 & 0xFF)) * (src >> 8 & 0xFF)
				+ (dest >> 24 & 0xFF) * (dest >> 8 & 0xFF)) / 256) << 8
		| (((256 - (dest >> 24 & 0xFF)) * (src & 0xFF)
				+ (dest >> 24 & 0xFF) * (dest & 0xFF)) / 256));
}

/*
 *	Creates a separete shade of the BXPM image with the light shade.
 *	Saves it to bxpm->shade[light from -100% -> +100].
 */
static void	shade_bxpm(t_doom *doom, int texture, int light)
{
	int		i;
	t_bxpm	*bxpm;

	i = -1;
	if (texture < 0 || doom->mtx[texture].shade[light] != NULL)
		return ;
	bxpm = &doom->mtx[texture];
	if (light == 100)
		bxpm->shade[100] = bxpm->clr;
	else
	{
		bxpm->shade[light] = protalloc(sizeof(Uint32) * bxpm->clr_nb);
		while (++i < bxpm->clr_nb)
		{
			if (bxpm->clr[i] == 0xFF800080)
				bxpm->shade[light][i] = 0xFF800080;
			bxpm->shade[light][i] = brightness(bxpm->clr[i], light);
		}
	}
}

/*
 *	Check all the sectors light levels and textures, if a textures does not
 *	have the light shade then it creates one.
 */
void	sector_shading(t_doom *doom, int s, int w)
{
	t_sector		*sector;

	s = -1;
	while (++s < doom->nb.sectors)
	{
		w = -1;
		sector = &doom->sectors[s];
		while (++w < sector->npoints)
			shade_bxpm(doom, sector->wall[w]->wtx, sector->light);
		shade_bxpm(doom, sector->floor.tx, sector->light);
		shade_bxpm(doom, sector->ceiling.tx, sector->light);
	}
	s = -1;
	while (++s < doom->nb.events)
	{
		if (doom->events[s].type != LIGHT)
			continue ;
		w = -1;
		sector = doom->events[s].sector;
		while (++w < sector->npoints)
			shade_bxpm(doom, sector->wall[w]->wtx, doom->events[s].light);
		shade_bxpm(doom, sector->floor.tx, doom->events[s].light);
		shade_bxpm(doom, sector->ceiling.tx, doom->events[s].light);
	}
}
