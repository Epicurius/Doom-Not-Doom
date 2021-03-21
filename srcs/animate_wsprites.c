
#include "doom.h"

int	animate_wsprite(t_doom *doom, t_sprite *sprite)
{
	if (sprite->time - doom->fps.curr < -100)
	{
		sprite->x += doom->textures[sprite->t].w;
		sprite->frame += 1;
		if (sprite->x >= doom->textures[sprite->t].surface->w)
		{
			sprite->x = 0;
			sprite->y += doom->textures[sprite->t].h;
		}
		if (sprite->frame >= doom->textures[sprite->t].nb ||
			sprite->y >= doom->textures[sprite->t].surface->h)
		{
			sprite->x = 0;
			sprite->y = 0;
			sprite->frame = 0;
		}
		sprite->time = doom->fps.curr;
	}
	return (1);
}
/*
int	animate_wsprite(t_doom *doom, t_wall *wall, int x)
{
	t_sprite *sprite;

	if (wall->wsprite.num[x].time - doom->fps.curr < -100)
	{
		sprite = &wall->wsprite.num[x];
		sprite->x += doom->textures[sprite->t].w;
		if (sprite->x >= doom->textures[sprite->t].surface->w)
		{
			sprite->x = 0;
			sprite->y += doom->textures[sprite->t].y;
		}
		if (sprite->y >= doom->textures[sprite->t].surface->h)
		{
			sprite->x = 0;
			sprite->y = 0;
		}
		sprite->time = doom->fps.curr;
	}
	return (1);
}*/
