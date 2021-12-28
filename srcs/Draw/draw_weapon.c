/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:52:38 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/28 13:19:35 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	blit_bxpm2(SDL_Surface *surface, t_bxpm *bxpm, t_rect srcr, t_rect dstr)
{
	int				x, y, x1;
	Uint32			clr;
	Uint32			*dst;
	unsigned short	*pix;
	
	pix = &bxpm->pix[srcr.y1 * bxpm->w + srcr.x1];
	dst = &((Uint32 *)surface->pixels)[dstr.y1 * surface->w + dstr.x1];
	y = srcr.y1;
	while (y < srcr.y2)
	{
		x = srcr.x1;
		x1 = 0;
		while (x < srcr.x2)
		{
			clr = bxpm->clr[pix[x]];
			if ((clr >> 24 & 0xFF) != 0)
				dst[x1] = clr;
			x1++;
			x++;
		}
		y++;
		pix += bxpm->w;
		dst += surface->w;
	}
}

/*
 *	Weapon drawing thread function.
 */
int	weapon_thread(void *args)
{
	t_weapon_thread	*thread;

	thread = args;
	blit_bxpm2(thread->dst, thread->src, thread->srcr, thread->dstr);
	return (1);
}

// If change remember scaling.
# define NB_WEAPON_THREADS	10

/*
 *	Calculate frame scale of the weapon.
 */
static void	weapon_frame_scale(t_doom *doom, t_rect *srcr, t_rect *dstr)
{
	t_bxpm		*bxpm;
	t_weapon	*weapon;

	weapon = &doom->weapon[doom->player.equipped];
	bxpm = &weapon->bxpm[weapon->frame];
	dstr->x1 = doom->c.x + weapon->x_offset;
	dstr->y1 = doom->surface->h - bxpm->h - 1;
	dstr->w = bxpm->w;
	dstr->h = bxpm->h / NB_WEAPON_THREADS;
	srcr->x1 = 0;
	srcr->y1 = 0;
	srcr->w = bxpm->w;
	srcr->h = bxpm->h / NB_WEAPON_THREADS;
}

/*
 *	Calculate weapon frame and create threads.
 */
void	draw_weapon(t_doom *doom)
{
	int				y;
	t_rect			dstr;
	t_rect			srcr;
	t_weapon_thread	thread[NB_WEAPON_THREADS];

	if (doom->player.equipped < 0)
		return ;
	weapon_frame_scale(doom, &srcr, &dstr);
	y = -1;
	while (++y < NB_WEAPON_THREADS)
	{
		thread[y].src = &doom->weapon[doom->player.equipped].bxpm
			[doom->weapon[doom->player.equipped].frame];
		thread[y].dst = doom->surface;
		thread[y].srcr = rect_xywh(srcr.x1, y * srcr.h + srcr.y1, srcr.w, srcr.h);//fix
		thread[y].dstr = rect_xywh(dstr.x1, y * dstr.h + dstr.y1, dstr.w, dstr.h);
		tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	}
	tpool_wait(&doom->tpool);
}
