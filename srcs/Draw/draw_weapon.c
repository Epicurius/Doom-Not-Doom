/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:52:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/05 06:53:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	Weapon drawing thread function.
 */
int	weapon_thread(void *args)
{
	t_weapon_thread	*thread;

	thread = args;
	blit_bxpm_scaled(thread->dst, thread->dstr, thread->src, thread->srcr);
	return (1);
}

/*
 *	Calcualte frame scale of the weapon.
 */
static void	weapon_frame_scale(t_doom *doom, t_rect *srcr, t_rect *dstr)
{
	t_bxpm		*bxpm;
	t_weapon	*weapon;

	weapon = &doom->weapon[doom->player.equipped];
	bxpm = &weapon->bxpm[weapon->frame];
	dstr->w = bxpm->w * weapon->scale;
	dstr->h = bxpm->h * weapon->scale;
	dstr->w -= dstr->w % 10;
	dstr->h -= dstr->h % 10;
	dstr->x1 = (doom->surface->w - dstr->w) / weapon->x_offset;
	dstr->y1 = doom->surface->h - dstr->h;
	srcr->x1 = 0;
	srcr->y1 = 0;
	srcr->w = bxpm->w;
	srcr->h = bxpm->h;
	srcr->w -= srcr->w % 10;
	srcr->h -= srcr->h % 10;
}

/*
 *	Calculate weapon frame and create threads.
 */
void	draw_weapon(t_doom *doom)
{
	int				y;
	t_rect			dstr;
	t_rect			srcr;
	t_weapon_thread	thread[10];

	if (doom->player.equipped < 0)
		return ;
	weapon_frame_scale(doom, &srcr, &dstr);
	y = -1;
	while (++y < 10)
	{
		thread[y].src = &doom->weapon[doom->player.equipped].bxpm
		[doom->weapon[doom->player.equipped].frame];
		thread[y].srcr = rect_xywh(srcr.x1, srcr.y1 + (y * (srcr.h / 10)),
				srcr.w, srcr.h / 10);
		thread[y].dst = doom->surface;
		thread[y].dstr = rect_xywh(dstr.x1, dstr.y1 + (y * (dstr.h / 10)),
				dstr.w, dstr.h / 10);
		tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	}
	tpool_wait(&doom->tpool);
}
