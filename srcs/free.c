
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
	TTF_CloseFont(doom->time.font);
	TTF_CloseFont(doom->time.clock_font);
}

void	free_color_palet(t_bxpm *bxpm)
{
	int i;

	i = -1;
	while (++i < 512)
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
}

void	free_rifts(t_doom *doom)
{
	t_list *tmp;
	t_list *curr;

	curr = doom->rifts;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

void	free_textures(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < 6)
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
	while (++i < 3)
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

void	free_weapons(t_doom *doom)
{
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < doom->weapon[i].frames)
		{
			free(doom->weapon[i].bxpm[j].pix);
			free(doom->weapon[i].bxpm[j].clr);
		}
		free(doom->weapon[i].bxpm);
	}
}

void	free_sounds(t_doom *doom)
{
	int i;

	i = -1;
	while (++i < 2)
		Mix_FreeChunk(doom->sound[i]);
}

int	free_doom(t_doom *doom)
{
	free_map(doom);
	free_sprites(doom);
	free_rifts(doom);
	free_projectiles(doom);
	free_textures(doom);
	free_weapons(doom);
	free_sprite_pos(&doom->sheet[0]);
	free_sprite_pos(&doom->sheet[1]);
	free_sprite_pos(&doom->sheet[2]);
	SDL_FreeSurface(doom->time.surf);
	free_render_utils(doom);
	free_font(doom);
	free_sounds(doom);
	free_tpool(&doom->tpool);
	SDL_FreeSurface(doom->surface);
	SDL_DestroyWindow(doom->win);
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();
	ft_putstr("All is free!\n");
	free(doom);
	return (1);
}
