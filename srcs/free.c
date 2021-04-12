
#include "doom.h"

void	free_map(t_doom *doom, int i)
{
	ft_memdel((void**)&doom->vert);
	ft_memdel((void**)&doom->floors);
	ft_memdel((void**)&doom->ceilings);
	ft_memdel((void**)&doom->entity);
	i = -1;
	while (++i < doom->nb.walls)
		ft_memdel((void**)&doom->walls[i].wsprite);
	ft_memdel((void**)&doom->walls);
	i = -1;
	while (++i < doom->nb.sectors)
		ft_memdel((void**)&doom->sectors[i].wall);
	ft_memdel((void**)&doom->sectors);
}

void	free_textures_surface(t_doom *doom, int i)
{
	while (++i < 50)
		if (doom->textures[i].surface != NULL)
			SDL_FreeSurface(doom->textures[i].surface);
}

void	free_entity_texture(t_doom *doom, int i, t_texture_sheet *sprite)
{
	int j;
	int k;

	while (++i < 4)
	{
		j = -1;
		while (++j < sprite->nb[i][FRAMES])
		{
			//k = -1;
			//while (++k < sprite->nb[i][ANGLES])
			//	ft_memdel((void**)&sprite->pos[i][j][k]);
			ft_memdel((void**)&sprite->pos[i][j]);
		}
		ft_memdel((void**)&sprite->pos[i]);
	}
	ft_memdel((void**)&sprite->pos);
	SDL_FreeSurface(sprite->surface);
}

void	free_render_utils(t_doom *doom, int i)
{
	ft_memdel((void**)&doom->ybot);
	ft_memdel((void**)&doom->ytop);
	ft_memdel((void**)&doom->zbuffer);
}

void	free_font(t_doom *doom, int i)
{
	TTF_CloseFont(doom->fps.font);
	TTF_CloseFont(doom->clock_font);
}

int	free_doom(t_doom *doom)
{
	free_map(doom, -1);
	free_textures_surface(doom, -1);
	free_entity_texture(doom, -1, &doom->sprites[0]);
	free_entity_texture(doom, -1, &doom->sprites[1]);
	free_render_utils(doom, -1);
	free_font(doom, -1);
#ifndef JONY
	free_tpool(&doom->tpool);
#endif
	SDL_FreeSurface(doom->surface);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	ft_putstr("All is free!\n");
	free(doom);
	return (1);
}
