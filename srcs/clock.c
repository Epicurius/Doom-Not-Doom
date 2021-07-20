/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/20 14:40:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	get_time(time_t *t)
{
	*t = time(NULL);
}

static void	clock_to_bxpm(SDL_Surface *surf, t_bxpm *bxpm)
{
	int	i;

	i = -1;
	while (++i < bxpm->pix_nb)
	{
		if (((Uint8 *)surf->pixels)[i] == 0xFF)
			bxpm->pix[i] = 0;
		else
			bxpm->pix[i] = 1;
	}
}

void	init_clock(t_doom *doom, t_bxpm *bxpm)
{
	time_t		t;
	char		*str;
	t_time		*time;
	SDL_Surface	*tmp;

	get_time(&t);
	time = &doom->time;
	time->clock_fg = hex_to_sdl_color(CLOCK_FG_COLOR);
	time->clock_bg = hex_to_sdl_color(CLOCK_BG_COLOR);
	time->date = *localtime(&t);
	str = ft_sprintf("%02d:%02d:%02d", time->date.tm_hour,
			time->date.tm_min, time->date.tm_sec);
	tmp = TTF_RenderText_Shaded(doom->font.digi100, str,
			time->clock_fg, time->clock_bg);
	bxpm->w = tmp->w;
	bxpm->h = tmp->h;
	bxpm->clr_nb = 2;
	bxpm->pix_nb = tmp->w * tmp->h;
	bxpm->clr = ft_memalloc(sizeof(Uint32) * 2);
	bxpm->pix = ft_memalloc(sizeof(unsigned short) * (tmp->w * tmp->h));
	bxpm->clr[0] = CLOCK_FG_COLOR;
	bxpm->clr[1] = CLOCK_BG_COLOR;
	clock_to_bxpm(tmp, bxpm);
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
	str = ft_sprintf("%02d:%02d:%02d", time->date.tm_hour,
			time->date.tm_min, time->date.tm_sec);
	wall->wsprite.num[x].time = time->date.tm_sec;
	tmp = TTF_RenderText_Shaded(doom->font.digi100, str,
			time->clock_fg, time->clock_bg);
	clock_to_bxpm(tmp, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	SDL_FreeSurface(tmp);
	free(str);
	return (1);
}
