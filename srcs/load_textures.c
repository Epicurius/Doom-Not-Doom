
#include "doom.h"

void	init_clock(t_doom *doom)
{
	time_t t;
	struct tm curr_time;
	char *str;
	SDL_Color fc;
	SDL_Color bc;

	t = time(NULL);
	curr_time = *localtime(&t);
	str = ft_sprintf("%02d:%02d:%02d",curr_time.tm_hour,
			curr_time.tm_min, curr_time.tm_sec);
	bc = hex_to_sdl_color(0x000000ff);
	fc = hex_to_sdl_color(0xffffffff);
	SDL_Surface *tmp;
	tmp = TTF_RenderText_Shaded(doom->clock_font, str, fc, bc);
	free(str);
	doom->clock = SDL_ConvertSurface(tmp, doom->surface->format, 0);
	SDL_FreeSurface(tmp);
}

void	load_textures(t_doom *doom)
{
	init_clock(doom);
	load_bxpm(doom);
	init_alfred(doom, &doom->sprites[0]);
	init_spooky(doom, &doom->sprites[1]);
	color_palets(doom);
}

