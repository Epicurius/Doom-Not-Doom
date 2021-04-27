
#include "doom.h"

void	free_map(t_doom *doom)
{
	int i;

	ft_memdel((void*)&doom->vert);
	ft_memdel((void*)&doom->floors);
	ft_memdel((void*)&doom->ceilings);
	i = -1;
	while (++i < doom->nb.walls)
		ft_memdel((void*)&doom->walls[i].wsprite);
	ft_memdel((void*)&doom->walls);
	i = -1;
	while (++i < doom->nb.sectors)
		ft_memdel((void*)&doom->sectors[i].wall);
	ft_memdel((void*)&doom->sectors);
}

void	free_entity_pos(t_texture_sheet *sprite)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < sprite->nb[i][FRAMES])
			free(sprite->pos[i][j]);
		free(sprite->pos[i]);
	}
	free(sprite->pos);
}

void	free_render_utils(t_doom *doom)
{
	free(doom->zbuffer);
	free(doom->fustrum);
	free(doom->render);
}

void	free_font(t_doom *doom)
{
	TTF_CloseFont(doom->fps.font);
	TTF_CloseFont(doom->clock_font);
}

void	free_color_palets(t_doom *doom)
{
	int i;
	int j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 256 + 256)
		{
			if (doom->mtx[i].palet[j])
				free(doom->mtx[i].palet[j]);
		}
	}	
}

void	free_entities(t_doom *doom)
{
	t_list *tmp;
	t_list *curr;

	curr = doom->entity;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

int	free_doom(t_doom *doom)
{
	free_map(doom);
	free_entities(doom);
	free_entity_pos(&doom->sprites[0]);
	free_entity_pos(&doom->sprites[1]);
	free_color_palets(doom);
	SDL_FreeSurface(doom->clock);
	SDL_FreeSurface(doom->fps.surf);
	free(doom->orb);
	free_render_utils(doom);
	free_font(doom);
	free_tpool(&doom->tpool);
	SDL_FreeSurface(doom->surface);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	TTF_Quit();
	ft_putstr("All is free!\n");
	free(doom);
	return (1);
}
