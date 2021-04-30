
#include "doom.h"

void	free_map(t_doom *doom)
{
	int i;

	ft_memdel((void*)&doom->vert);
	i = -1;
	while (++i < doom->nb.walls)
		ft_memdel((void*)&doom->walls[i].wsprite);
	ft_memdel((void*)&doom->walls);
	i = -1;
	while (++i < doom->nb.sectors)
		ft_memdel((void*)&doom->sectors[i].wall);
	ft_memdel((void*)&doom->sectors);
}

void	free_sprite_pos(t_texture_sheet *sprite)
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

void	free_color_palet(t_bxpm *bxpm)
{
	int i;

	while (++i < 256 + 256)
	{
		if (bxpm->palet[i])
			free(bxpm->palet[i]);
	}
}

void	free_sprites(t_doom *doom)
{
	t_list *tmp;
	t_list *curr;

	curr = doom->sprite;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	curr = doom->spawners;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	curr = doom->entities;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
	curr = doom->objects;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void	free_textures(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		free(doom->mtx[i].clr);
		free(doom->mtx[i].pix);
		free_color_palet(&doom->mtx[i]);
	}
	i = -1;
	while (++i < 12)
	{
		free(doom->stx[i].clr);
		free(doom->stx[i].pix);
	}
	i = -1;
	while (++i < 2)
	{
		free(doom->sheet[i].bxpm.clr);
		free(doom->sheet[i].bxpm.pix);
	}
}

void	free_projectiles(t_doom *doom)
{
	t_list *curr;
	t_list *del;
	curr = doom->orb;
	while (curr)
	{
		del = curr;
		curr = curr->next;
		free(del->content);
		free(del);
	}
}

int	free_doom(t_doom *doom)
{
	free_map(doom);
	free_sprites(doom);
	free_textures(doom);
	free_sprite_pos(&doom->sheet[0]);
	free_sprite_pos(&doom->sheet[1]);
	SDL_FreeSurface(doom->clock);
	SDL_FreeSurface(doom->fps.surf);
	free_projectiles(doom);
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
