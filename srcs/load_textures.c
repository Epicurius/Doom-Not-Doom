
#include "doom.h"

void	init_texture_values(t_texture *texture, t_xyz size)
{
	if (size.x == 0 || size.y == 0)
	{
		texture->nb = 1;
		texture->w = texture->surface->w;
		texture->h = texture->surface->h;
	}	
	else
	{
		texture->nb = size.z;
		texture->w = size.x;
		texture->h = size.y;
	}
	texture->ratio = (double)texture->h / (double)texture->w;
	texture->x = 0;
	texture->y = 0;
}

void	load_skybox_textures(t_doom *doom)
{
	int i;

	i = -1;
	doom->skybox_t[0].surface = IMG_Load("./bmp/skyboxes/back1.bmp");
	doom->skybox_t[1].surface = IMG_Load("./bmp/skyboxes/left1.bmp");
	doom->skybox_t[2].surface = IMG_Load("./bmp/skyboxes/front1.bmp");
	doom->skybox_t[3].surface = IMG_Load("./bmp/skyboxes/right1.bmp");
	doom->skybox_t[4].surface = IMG_Load("./bmp/skyboxes/bottom1.bmp");
	doom->skybox_t[5].surface = IMG_Load("./bmp/skyboxes/top1.bmp");
	while (++i < NB_SKYBOX_TEXTURES)
		init_texture_values(&doom->skybox_t[i], xyz(0,0,0));
}

void	init_clock(t_doom *doom);
//precalc width / scale
void	load_map_textures(t_doom *doom)
{
	t_xyz size;
	int i;

	i = 0;
	//doom->textures[0].surface = IMG_Load("./bmp/walls/alloy.bmp");
	doom->textures[1].surface = IMG_Load("./bmp/walls/grass.bmp");
	doom->textures[2].surface = IMG_Load("./bmp/walls/wood.bmp");
	doom->textures[3].surface = IMG_Load("./bmp/walls/stone.bmp");
	doom->textures[4].surface = IMG_Load("./bmp/walls/alloy.bmp");
	while (++i < 5)
		init_texture_values(&doom->textures[i], xyz(0,0,0));

	doom->textures[26].surface = IMG_Load("./bmp/wsprites/vent.bmp");
	init_texture_values(&doom->textures[26], xyz(64,64,4));
	doom->textures[27].surface = IMG_Load("./bmp/entities/imp2.bmp");
	init_texture_values(&doom->textures[27], xyz(0,0,0));
	doom->textures[47].surface = IMG_Load("./bmp/wsprites/clown.bmp");
	init_texture_values(&doom->textures[47], xyz(100,94,40));
	doom->textures[48].surface = IMG_Load("./bmp/wsprites/bh3.bmp");
	init_texture_values(&doom->textures[48], xyz(0,0,0));
}

void	load_textures(t_doom *doom)
{
	load_skybox_textures(doom);
	load_map_textures(doom);
	init_clock(doom);
	init_alfred(doom, &doom->sprites[0]);
	init_spooky(doom, &doom->sprites[1]);
}

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
	doom->textures[49].surface =
			SDL_ConvertSurface(tmp, doom->surface->format, 0);
	SDL_FreeSurface(tmp);
	init_texture_values(&doom->textures[49], xyz(0,0,0));
}
