/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:52:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/21 12:33:43 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

typedef struct s_weapon_thread
{
	SDL_Surface	*dst;
	t_rect		dstr;
	t_bxpm		*src;
	t_rect		srcr;	
}				t_weapon_thread;

static int	weapon_thread(t_weapon_thread *thread)
{
	blit_bxpm_scaled(thread->dst, thread->dstr, thread->src, thread->srcr);
	return (1);
}

static void	draw_weapon2(t_doom *doom, t_rect *srcr, t_rect *dstr)
{
	t_bxpm		*bxpm;
	t_weapon	*weapon;

	weapon = &doom->weapon[doom->player.equiped];
	bxpm = &weapon->bxpm[weapon->frame];
	dstr->w = bxpm->w * weapon->scale;
	dstr->h = bxpm->h * weapon->scale;
	//dstr->w -= dstr->w % 10;
	//dstr->h -= dstr->h % 10;
	dstr->x1 = (doom->surface->w - dstr->w) / weapon->x_offset;
	dstr->y1 = doom->surface->h - dstr->h;
	srcr->x1 = 0;
	srcr->y1 = 0;
	srcr->w = bxpm->w;
	srcr->h = bxpm->h;
	//srcr->w -= srcr->w % 10;
	//srcr->h -= srcr->h % 10;
	//printf("%d %d %d %d\n", srcr->w, srcr->h, dstr->w, dstr->h);
}

# define TESST 10

void	draw_weapon(t_doom *doom)
{
	int				y;
	t_rect			dstr;
	t_rect			srcr;
	t_weapon_thread	thread[10];

	if (doom->player.equiped < 0)
		return ;
	draw_weapon2(doom, &srcr, &dstr);
	y = -1;
	while (++y < 10)
	{
		thread[y].src = &doom->weapon[doom->player.equiped].bxpm[doom->weapon[doom->player.equiped].frame];

		thread[y].srcr = rect_xywh(srcr.x1, srcr.y1 + (y * (srcr.h / TESST)), srcr.w, srcr.h / TESST);
		thread[y].dst = doom->surface;
		thread[y].dstr = rect_xywh(dstr.x1, dstr.y1 + (y * (dstr.h / TESST)), dstr.w, dstr.h / TESST);
		tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	}
	tpool_wait(&doom->tpool);
}
