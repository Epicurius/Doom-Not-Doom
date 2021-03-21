
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
** -x darker, 0 nothing, +x lighter
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
