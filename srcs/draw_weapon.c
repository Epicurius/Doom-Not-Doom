/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:52:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/25 15:55:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef struct	s_weapon_thread
{
	SDL_Surface	*dst;
	t_rect		dstr;
	t_bxpm		*src;
	t_rect		srcr;	
}				t_weapon_thread;

int		weapon_thread(t_weapon_thread *thread)
{
	blit_bxpm_scaled(thread->dst, thread->dstr, thread->src, thread->srcr);
	return (1);
}

void	draw_weapon(t_doom *doom)
{
	t_rect dstr;
	t_rect srcr;
	t_bxpm *bxpm;
	t_weapon *weapon;
	t_weapon_thread thread[10];
	int t = 10;
	int y = -1;

	if (doom->player.equiped < 0)
		return ;
	weapon = &doom->weapon[doom->player.equiped];
	bxpm = &weapon->bxpm[weapon->frame];

	dstr.w = bxpm->w * weapon->scale;
	dstr.h = bxpm->h * weapon->scale;
	dstr.x1 = (doom->surface->w - dstr.w) / weapon->x_offset;
	dstr.y1 = doom->surface->h - dstr.h;

	srcr.x1 = 0;
	srcr.y1 = 0;
	srcr.w = weapon->bxpm[weapon->frame].w;
	srcr.h = weapon->bxpm[weapon->frame].h;
	while (++y < t)
	{
		thread[y].src = &weapon->bxpm[weapon->frame];
		thread[y].srcr = rect_xywh(srcr.x1, srcr.y1 + (y * (srcr.h / t)), srcr.w, srcr.h / t);
		thread[y].dst = doom->surface;
		thread[y].dstr = rect_xywh(dstr.x1, dstr.y1 + (y * (dstr.h / t)), dstr.w, dstr.h / t);
		tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	}
	tpool_wait(&doom->tpool);
}
