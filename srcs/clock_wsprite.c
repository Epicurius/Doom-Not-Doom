
#include "doom.h"


//	fix 49
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
	if (doom->textures[49].surface != NULL)
		SDL_FreeSurface(doom->textures[49].surface);
	SDL_Surface *tmp;
	tmp = TTF_RenderText_Shaded(doom->clock_font, str, fc, bc);
	free(str);
	if (tmp == NULL)
		return (0);	
	doom->textures[49].surface =
			SDL_ConvertSurface(tmp, doom->surface->format, 0);
	SDL_FreeSurface(tmp);
	return (1);
}

int	clock_wsprite(t_doom *doom, t_wall *wall, int x)
{
	wall->wsprite.num[x].ready = 0;
	if (!(clock_digital_wsprite(doom, wall, x)))
		return (0);
	return (1);
}

/*
int	clock_analog_wsprite(t_doom *doom, t_wall *wall, int x)
{
	time_t t;
	struct tm curr_time;
	char *str;
	t_i2 p[2];

	wall->wsprite.num[x].ready = 0;
	t = time(NULL);
	curr_time = *localtime(&t);
	double min = (360.0 / 60.0) * (double)curr_time.tm_min;
	double h = (360.0 / 720.0) * (double)(curr_time.tm_hour * 60 + curr_time.tm_min);

	int i = -1;
	SDL_BlitSurface(doom->textures[NB_WALL_TEXTURES - 1].surface, NULL, doom->clock, NULL);
	//while (++i < 551 * 551)
	//{
	//	((Uint32*)doom->textures[NB_WALL_TEXTURES - 1].surface->pixels)[i]
	//			= ((Uint32*)doom->clock->pixels)[i];
	//}
	p[0].x = doom->textures[NB_WALL_TEXTURES - 1].w / 2;
	p[0].y = doom->textures[NB_WALL_TEXTURES - 1].h / 2;
	double d = (min - 90) * CONVERT_RADIANS;
	p[1].x = p[0].x + ((p[0].x - 75) * cos(d));
	p[1].y = p[0].y + ((p[0].x - 75) * sin(d));
	line(doom->textures[NB_WALL_TEXTURES - 1].surface, 0x000000, p);
	p[0].x = doom->textures[NB_WALL_TEXTURES - 1].w / 2;
	p[0].y = doom->textures[NB_WALL_TEXTURES - 1].h / 2;
	d = (h - 90) * CONVERT_RADIANS;
	p[1].x = p[0].x + ((p[0].x - 125) * cos(d));
	p[1].y = p[0].y + ((p[0].x - 125) * sin(d));
	line(doom->textures[NB_WALL_TEXTURES - 1].surface, 0xff0000, p);
	return (1);
}
*/

