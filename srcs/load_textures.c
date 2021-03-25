
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
	init_clock(doom);
}

void	load_entities_textures(t_doom *doom)
{
	int i;

	i = -1;
	doom->entity_t[0].surface = IMG_Load("./bmp/entities/imp.bmp");
	doom->entity_t[1].surface = IMG_Load("./bmp/entities/hd1.bmp");
	while (++i < 2)
		init_texture_values(&doom->entity_t[i], xyz(0,0,0));
	doom->entity_t[2].surface = IMG_Load("./bmp/wsprites/clown.bmp");
	init_texture_values(&doom->entity_t[2], xyz(100,94,40));
	
}

/*
t_rect		new_rect(int x1, int y1, int x2, int y2)
{
	t_rect new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x2;
	new.y2 = y2;
	new.w = new.x2 - new.x1;
	new.h = new.y2 - new.y1;
	new.ratio = (double)new.w / (double)new.h;
	return (new);
}

int	init_alfred(t_doom *doom, t_texture_sheet *sprite)
{
	int i;
	
	sprite->surface = IMG_Load("./bmp/entities/head_fix2.bmp");
	sprite->nb[IDLE][FRAMES] = 1;
	sprite->nb[IDLE][ANGLES] = 8;
	sprite->nb[MOVE][FRAMES] = 1;
	sprite->nb[MOVE][ANGLES] = 8;
	sprite->nb[ATTACK][FRAMES] = 6;
	sprite->nb[ATTACK][ANGLES] = 1;
	sprite->nb[DEATH][FRAMES] = 0;
	sprite->nb[DEATH][ANGLES] = 0;
	sprite->pos = (t_rect***)ft_memalloc(sizeof(t_rect**) * 4);

	i = -1;
	if (sprite->nb[IDLE][FRAMES] > 0)
		sprite->pos[IDLE] = ft_memalloc(sizeof(t_rect*) * sprite->nb[IDLE][FRAMES]);
	while (++i < sprite->nb[IDLE][FRAMES])
		sprite->pos[IDLE][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[IDLE][ANGLES]);
	i = -1;
	if (sprite->nb[MOVE][FRAMES] > 0)
		sprite->pos[MOVE] = ft_memalloc(sizeof(t_rect*) * sprite->nb[MOVE][FRAMES]);
	while (++i < sprite->nb[MOVE][FRAMES])
		sprite->pos[MOVE][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[MOVE][ANGLES]);
	i = -1;
	if (sprite->nb[ATTACK][FRAMES] > 0)
		sprite->pos[ATTACK] = ft_memalloc(sizeof(t_rect*) * sprite->nb[ATTACK][FRAMES]);
	while (++i < sprite->nb[ATTACK][FRAMES])
		sprite->pos[ATTACK][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[ATTACK][ANGLES]);
	i = -1;
	if (sprite->nb[DEATH][FRAMES] > 0)
		sprite->pos[DEATH] = ft_memalloc(sizeof(t_rect*) * sprite->nb[DEATH][FRAMES]);
	while (++i < sprite->nb[DEATH][FRAMES])
		sprite->pos[DEATH][i] = ft_memalloc(sizeof(t_rect) * sprite->nb[DEATH][ANGLES]);


	sprite->pos[0][0][4] = new_rect(45,  33, 88,  79);
	sprite->pos[0][0][5] = new_rect(133, 33, 163, 79);
	sprite->pos[0][0][6] = new_rect(210, 33, 239, 86);
	sprite->pos[0][0][7] = new_rect(283, 33, 317, 84);
	sprite->pos[0][0][0] = new_rect(362, 33, 405, 78);
	sprite->pos[0][0][1] = new_rect(424, 33, 456, 85);
	sprite->pos[0][0][2] = new_rect(500, 33, 531, 87);
	sprite->pos[0][0][3] = new_rect(576, 33, 607, 79);

	sprite->pos[1][0][4] = new_rect(45,  33, 88,  79);
	sprite->pos[1][0][5] = new_rect(133, 33, 163, 79);
	sprite->pos[1][0][6] = new_rect(210, 33, 239, 86);
	sprite->pos[1][0][7] = new_rect(283, 33, 317, 84);
	sprite->pos[1][0][0] = new_rect(362, 33, 405, 78);
	sprite->pos[1][0][1] = new_rect(424, 33, 456, 85);
	sprite->pos[1][0][2] = new_rect(500, 33, 531, 87);
	sprite->pos[1][0][3] = new_rect(576, 33, 607, 79);


	sprite->pos[2][0][0] = new_rect(44,  449,  78, 499);
	sprite->pos[2][1][0] = new_rect(122, 449, 158, 500);
	sprite->pos[2][2][0] = new_rect(203, 449, 247, 496);
	sprite->pos[2][3][0] = new_rect(291, 449, 359, 508);
	sprite->pos[2][4][0] = new_rect(403, 449, 491, 520);
	sprite->pos[2][5][0] = new_rect(539, 449, 638, 537);
	return (1);
}

int	init_spooky(t_doom *doom)
{
	doom->spooky.surface = IMG_Load("./bmp/entities/Spooky.bmp");
	doom->spooky.pos = ft_memalloc(sizeof(t_rect) * 14);
	//sprite->pos[0]	= 0;
	//sprite->follow = 8;
	//sprite->death	= 13;
	//sprite->flee	= ft_memalloc(sizeof(t_rect) * 5);
	//sprite->death = ft_memalloc(sizeof(t_rect) * 6);


	sprite->pos[4] = new_rect(45,	33, 88,	 79);
	sprite->pos[5] = new_rect(133, 33, 163, 79);
	sprite->pos[6] = new_rect(210, 33, 239, 86);
	sprite->pos[7] = new_rect(283, 33, 317, 84);
	sprite->pos[0] = new_rect(362, 33, 405, 78);
	sprite->pos[1] = new_rect(424, 33, 456, 85);
	sprite->pos[2] = new_rect(500, 33, 531, 87);
	sprite->pos[3] = new_rect(576, 33, 607, 79);

	sprite->pos[8] = new_rect(44,  449,  78, 499);
	sprite->pos[9] = new_rect(122, 449, 158, 500);
	sprite->pos[10] = new_rect(203, 449, 247, 496);
	sprite->pos[11] = new_rect(291, 449, 359, 508);
	sprite->pos[12] = new_rect(403, 449, 491, 520);
	sprite->pos[13] = new_rect(539, 449, 638, 537);
	return (1);
}*/

void	load_textures(t_doom *doom)
{
	load_skybox_textures(doom);
	load_map_textures(doom);
	load_entities_textures(doom);
	init_alfred(doom, &doom->sprites[0]);
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

/*
int	init_demon(t_doom *doom)
{
	sprite->surface = IMG_Load("./bmp/entities/demon2.bmp");
	sprite->total = 9;
	sprite->pos = ft_memalloc(sizeof(t_rect) * 9);
	sprite->pos[0] = new_rect(0, 0, 84, 108);
	sprite->pos[7] = new_rect(129, 0, 202, 108);
	sprite->pos[6] = new_rect(247, 0, 305, 108);
	sprite->pos[5] = new_rect(349, 0, 434, 108);
	sprite->pos[4] = new_rect(478, 0, 562, 108);
	sprite->pos[3] = new_rect(606, 0, 682, 108);
	sprite->pos[2] = new_rect(725, 0, 784, 108);
	sprite->pos[1] = new_rect(828, 0, 911, 108);
	return (1);
	
}*/


