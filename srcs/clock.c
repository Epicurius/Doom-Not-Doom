/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clock.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:24:23 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/07 16:27:17 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


/*
 *	Simple pixel copy from SDL_Surface fo BXPM. 
 *	(Clock has only 2 colors black and white which makes this a lot faster)
 */
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

/*
 *	Inits clock wall sprite.
 */
void	init_clock(t_doom *doom, t_bxpm *bxpm)
{
	char		*str;
	t_time		*t;
	SDL_Surface	*tmp;

	doom->time.start = time(NULL);
	//get_time(&doom->time.start);
	t = &doom->time;
	t->clock_fg = hex_to_sdl_color(CLOCK_FG_COLOR);
	t->clock_bg = hex_to_sdl_color(CLOCK_BG_COLOR);
	t->date = *localtime(&doom->time.start);
	str = ft_sprintf("%02d:%02d:%02d", t->date.tm_hour,
			t->date.tm_min, t->date.tm_sec);
	tmp = TTF_RenderText_Shaded(doom->font.digital, str,
			t->clock_fg, t->clock_bg);
	bxpm->w = tmp->w;
	bxpm->h = tmp->h;
	bxpm->clr_nb = 2;
	bxpm->pix_nb = tmp->w * tmp->h;
	bxpm->clr = protalloc(sizeof(Uint32) * 2);
	bxpm->pix = protalloc(tmp->w * tmp->h * 2);
	bxpm->clr[0] = CLOCK_FG_COLOR;
	bxpm->clr[1] = CLOCK_BG_COLOR;
	clock_to_bxpm(tmp, bxpm);
	SDL_FreeSurface(tmp);
	free(str);
}

/*
 *	Handles the updating of the clock bxpm.
 *	Only if the time has changed (second).
 */
int	clock_wsprite(t_doom *doom, t_wall *wall, int x)
{
	char		*str;
	time_t		tm;
	t_time		*t;
	SDL_Surface	*tmp;

	tm = time(NULL);
	//get_time(&t);
	t = &doom->time;
	t->date = *localtime(&tm);
	if (wall->wsprite.num[x].time == t->date.tm_sec)
		return (1);
	str = ft_sprintf("%02d:%02d:%02d", t->date.tm_hour,
			t->date.tm_min, t->date.tm_sec);
	wall->wsprite.num[x].time = t->date.tm_sec;
	tmp = TTF_RenderText_Shaded(doom->font.digital, str,
			t->clock_fg, t->clock_bg);
	clock_to_bxpm(tmp, &doom->mtx[MAP_TEXTURE_AMOUNT - 1]);
	SDL_FreeSurface(tmp);
	free(str);
	return (1);
}

char *get_elapsed_time_str(t_doom *doom)
{
    int elapsed;
	int h;
	int m;
	int	s;
	
	elapsed = time(NULL) - doom->time.start;
	h = elapsed / 3600;
	elapsed -= (h * 3600);
	m = elapsed / 60;
	elapsed -= (m * 60);
	s = elapsed;
	return (ft_sprintf("%02d:%02d:%02d", h, m, s));	
}