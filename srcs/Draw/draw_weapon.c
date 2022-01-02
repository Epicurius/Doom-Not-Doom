/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:52:38 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/02 11:07:11 by nneronin         ###   ########.fr       */
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
	blit_bxpm(thread, thread->dst, thread->src);
	return (1);
}

/*
 *	Calculate frame scale of the weapon.
 */
static void	init_first_weapon_thread(t_doom *doom, t_weapon_thread *thread,
	int w, int h)
{
	thread->dx1 = doom->c.x + doom->weapon[doom->player.equipped].x_offset;
	thread->dy1 = doom->surface->h - thread->src->h - 1;
	thread->dx2 = thread->dx1 + w;
	thread->dy2 = thread->dy1 + h;
	thread->sx1 = 0;
	thread->sy1 = 0;
	thread->sx2 = thread->sx1 + w;
	thread->sy2 = thread->sy1 + h;
}

/*
 *	Calculate weapon frame and create threads.
 */
void	draw_weapon(t_doom *doom)
{
	int				y;
	int				w;
	int				h;
	t_weapon_thread	thread[NB_WEAPON_THREADS];

	y = 0;
	thread[y].dst = doom->surface;
	thread[y].src = &doom->weapon[doom->player.equipped]
		.bxpm[doom->weapon[doom->player.equipped].frame];
	w = thread[y].src->w;
	h = thread[y].src->h / NB_WEAPON_THREADS;
	init_first_weapon_thread(doom, &thread[y], w, h);
	tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	while (++y < NB_WEAPON_THREADS)
	{
		thread[y] = (t_weapon_thread){
			thread[y - 1].dst, thread[y - 1].src,
			thread[y - 1].sx1, thread[y].sy1 + h,
			thread[y - 1].sx2, thread[y - 1].sy2,
			thread[y - 1].dx1, thread[y].dy1 + h,
			thread[y - 1].dx2, thread[y - 1].dy2};
		tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	}
	tpool_wait(&doom->tpool);
}
