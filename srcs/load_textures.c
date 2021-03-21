
#include "doom.h"

void	init_texture_values(t_texture *texture, t_xyz size)
{
	if (size.x == 0 || size.y == 0)
	{
		texture->nb_w = 1;
		texture->nb_h = 1;
		texture->nb = 1;
		texture->w = texture->surface->w;
		texture->h = texture->surface->h;
	}	
	else
	{
		texture->nb_w = floor(texture->surface->w / size.x);
		texture->nb_h = floor(texture->surface->h / size.y);
		texture->nb = size.z;
		texture->w = size.x;
		texture->h = size.y;
	}
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

//precalc width / scale
void	load_map_textures(t_doom *doom)
{
	t_xyz size;
	int i;

	i = -1;
	doom->textures[0].surface = IMG_Load("./bmp/walls/alloy.bmp");
	doom->textures[1].surface = IMG_Load("./bmp/walls/grass.bmp");
	doom->textures[2].surface = IMG_Load("./bmp/walls/wood.bmp");
	doom->textures[3].surface = IMG_Load("./bmp/walls/stone.bmp");
	while (++i < 4)
		init_texture_values(&doom->textures[i], xyz(0,0,0));

	doom->textures[26].surface = IMG_Load("./bmp/wsprites/vent.bmp");
	init_texture_values(&doom->textures[26], xyz(64,64,4));
	doom->textures[47].surface = IMG_Load("./bmp/wsprites/clown.bmp");
	init_texture_values(&doom->textures[47], xyz(100,94,40));
	doom->textures[48].surface = IMG_Load("./bmp/wsprites/bh3.bmp");
	init_texture_values(&doom->textures[48], xyz(0,0,0));
}

void	load_entities_textures(t_doom *doom)
{
	int i;

	i = -1;
	doom->entity_t[0].surface = IMG_Load("./bmp/entities/imp.bmp");
	doom->entity_t[1].surface = IMG_Load("./bmp/entities/hd1.bmp");
	while (++i < 2)
		init_texture_values(&doom->entity_t[i], xyz(0,0,0));
}

void	load_textures(t_doom *doom)
{
	load_skybox_textures(doom);
	load_map_textures(doom);
	load_entities_textures(doom);
	doom->textures[49].x = 0;
	doom->textures[49].y = 5;
	doom->textures[49].w = 45 * 8;
	doom->textures[49].h = 73; 
}
