
#include "doom.h"

int	clock_digital_wsprite(t_doom *doom, t_wall *wall, int x)
{
	time_t t;
	struct tm curr_time;
	char *str;
	SDL_Color fc;
	SDL_Color bc;

	t = time(NULL);
	curr_time = *localtime(&t);
	if (wall->wsprite.num[x].time == curr_time.tm_sec)
		return (1);
	str = ft_sprintf("%02d:%02d:%02d",curr_time.tm_hour,
			curr_time.tm_min, curr_time.tm_sec);
	wall->wsprite.num[x].time = curr_time.tm_sec;
	bc = hex_to_sdl_color(0x000000ff);
	fc = hex_to_sdl_color(0xffffffff);
	SDL_FreeSurface(doom->clock);
	SDL_Surface *tmp;
	tmp = TTF_RenderText_Shaded(doom->clock_font, str, fc, bc);
	free(str);
	if (tmp == NULL)
		return (0);	
	doom->clock = SDL_ConvertSurface(tmp, doom->surface->format, 0);
	SDL_FreeSurface(tmp);
	wall->wsprite.num[x].src = new_rect(0, 0, doom->clock->w, doom->clock->h);
	return (1);
}

int	clock_wsprite(t_doom *doom, t_wall *wall, int x)
{
	wall->wsprite.num[x].ready = 0;
	if (!(clock_digital_wsprite(doom, wall, x)))
		return (0);
	return (1);
}
