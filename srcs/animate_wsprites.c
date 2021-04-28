
#include "doom.h"

int	animate_wsprite(t_doom *doom, t_wsprite *sprite)
{
	if (sprite->time - doom->fps.curr < -100)
	{
		sprite->src.x1 += 64;
		sprite->frame += 1;
		if (sprite->src.x1 >= doom->mtx[sprite->tx].w)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 += 64;
		}
		if (sprite->frame >= 3 || sprite->src.y1 >= doom->mtx[sprite->tx].h)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 = 0;
			sprite->frame = 0;
		}
		sprite->src.x2 = sprite->src.x1 + 64;
		sprite->src.y2 = sprite->src.y1 + 64;
		sprite->time = doom->fps.curr;
	}
	return (1);
}
/*
int	animate_wsprite(t_doom *doom, t_wsprite *sprite)
{
	if (sprite->time - doom->fps.curr < -100)
	{
		sprite->src.x1 += doom->textures[sprite->tx].w;
		sprite->frame += 1;
		if (sprite->src.x1 >= doom->textures[sprite->tx].surface->w)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 += doom->textures[sprite->tx].h;
		}
		if (sprite->frame >= doom->textures[sprite->tx].nb ||
			sprite->src.y1 >= doom->textures[sprite->tx].surface->h)
		{
			sprite->src.x1 = 0;
			sprite->src.y1 = 0;
			sprite->frame = 0;
		}
		sprite->src.x2 = sprite->src.x1 + doom->textures[sprite->tx].w;
		sprite->src.y2 = sprite->src.y1 + doom->textures[sprite->tx].h;
		sprite->time = doom->fps.curr;
	}
	return (1);
}*/
