/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/12 10:46:02 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	get_time(time_t *t)
{
	*t = time(NULL);
}

void	clock_to_bxpm(SDL_Surface *surf, t_bxpm *bxpm)
{
	int i;

	i = -1;
	while (++i < bxpm->pix_nb)
	{
		if (((Uint8*)surf->pixels)[i] == 0xFF)
			bxpm->pix[i] = 0;
		else
			bxpm->pix[i] = 1;
	}
}

void	init_clock(t_doom *doom)
{
	char		*str;
	time_t		t;
	t_time		*time;
	SDL_Surface	*tmp;

	get_time(&t);
	time = &doom->time;
	time->clock_fg = hex_to_sdl_color(CLOCK_FG_COLOR);
	time->clock_bg = hex_to_sdl_color(CLOCK_BG_COLOR);
	time->date = *localtime(&t);
	str = ft_sprintf("%02d:%02d:%02d", time->date.tm_hour, time->date.tm_min, time->date.tm_sec);
	tmp = TTF_RenderText_Shaded(time->font, str, time->clock_fg, time->clock_bg);
	doom->mtx[4].w = tmp->w;
	doom->mtx[4].h = tmp->h;
	doom->mtx[4].clr_nb = 2;
	doom->mtx[4].pix_nb = tmp->w * tmp->h;
	doom->mtx[4].clr = ft_memalloc(sizeof(uint32_t) * 2);
	doom->mtx[4].pix = ft_memalloc(sizeof(unsigned short) * (tmp->w * tmp->h));
	doom->mtx[4].clr[0] = CLOCK_FG_COLOR;
	doom->mtx[4].clr[1] = CLOCK_BG_COLOR;
	clock_to_bxpm(tmp, &doom->mtx[4]);
	SDL_FreeSurface(tmp);
	free(str);
}

int	clock_wsprite(t_doom *doom, t_wall *wall, int x)
{
	char		*str;
	time_t		t;
	t_time		*time;
	SDL_Surface	*tmp;

	get_time(&t);
	time = &doom->time;
	time->date = *localtime(&t);
	if (wall->wsprite.num[x].time == time->date.tm_sec)
		return (1);
	str = ft_sprintf("%02d:%02d:%02d", time->date.tm_hour, time->date.tm_min, time->date.tm_sec);
	wall->wsprite.num[x].time = time->date.tm_sec;
	tmp = TTF_RenderText_Shaded(time->font, str, time->clock_fg, time->clock_bg);
	clock_to_bxpm(tmp, &doom->mtx[4]);
	SDL_FreeSurface(tmp);
	free(str);
	return (1);
}
