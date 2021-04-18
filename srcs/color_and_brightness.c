
#include "doom.h"

SDL_Color	hex_to_sdl_color(int hex)
{
	SDL_Color color;

	color.r = hex >> 24;
	color.g = hex >> 16;
	color.b = hex >> 8;
	color.a = hex;
	return (color);
}

/*
** Darkens or brightens a color 
** -x darker, 0 nothing, +x lighter obvs -255 to 255
*/
Uint32		brightness(Uint32 src, int brightness)
{
	if (brightness == 0)
		return (src);
	src = ft_clamp(((brightness + 256) * (src >> 16 & 0xFF)) / 256, 0, 255)
	<< 16 | ft_clamp(((brightness + 256) * (src >> 8 & 0xFF)) / 256, 0, 255)
	<< 8 | ft_clamp(((brightness + 256) * (src & 0xFF)) / 256, 0, 255);
	return (src);
}

/*
** Blends a src color with an alpha 0 - 255
*/
unsigned int	blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha)
{
	int	aalpha;

	aalpha = 256 - alpha;
	return (
		((aalpha * (src >> 16 & 0xFF) + alpha * (dest >> 16 & 0xFF)) / 256)
		<< 16
		| ((aalpha * (src >> 8 & 0xFF) + alpha * (dest >> 8 & 0xFF)) / 256)
		<< 8
		| ((aalpha * (src & 0xFF) + alpha * (dest & 0xFF)) / 256));
}

void	color_palet(t_bxpm *bxpm, int light)
{
	int i;

	i = -1;
	if (bxpm->palet[255 + light])
		return ;
	bxpm->palet[255 + light] = ft_memalloc(sizeof(uint32_t*) * bxpm->clr_nb);
	while (++i < bxpm->clr_nb)
	{
		if (bxpm->clr[i] == 0x800080)
			bxpm->palet[255 + light][i] = 0x800080;
		bxpm->palet[255 + light][i] = brightness(bxpm->clr[i], light);
	}
}

void	color_palets(t_doom *doom)
{
	int s;
	int w;
	t_sector *sector;
	

	s = -1;
	while (++s < doom->nb.sectors)
	{
		w = -1;
		sector = &doom->sectors[s];
		while (++w < doom->sectors[s].npoints)
		{
			color_palet(&doom->mtx[sector->wall[w]->wtx], sector->light);
		}
		color_palet(&doom->mtx[sector->floor.tx], sector->light);
		color_palet(&doom->mtx[sector->ceiling.tx], sector->light);
		
	}
}
