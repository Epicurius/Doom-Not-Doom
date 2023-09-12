/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	Weapon drawing thread function.
 */
int	weapon_thread(void *args)
{
	t_weapon_thread	*thread;

	thread = args;
	blit_bxpm2(thread, thread->dst, thread->src);
	return (1);
}

/*
 *	Calculate frame scale of the weapon.
 */
static void	init_first_weapon_thread(t_doom *doom, t_weapon_thread *thread)
{
	thread->dx1 = doom->c.x + doom->weapon[doom->player.equipped].x_offset;
	thread->dy1 = doom->surface->h - thread->src->h - 1;
	thread->dx2 = thread->dx1 + thread->src->w;
	thread->dy2 = thread->dy1 + thread->src->h / NB_WEAPON_THREADS;
	thread->sx1 = 0;
	thread->sy1 = 0;
	thread->sx2 = thread->sx1 + thread->src->w;
	thread->sy2 = thread->sy1 + thread->src->h / NB_WEAPON_THREADS;
}

/*
 *	Calculate weapon frame and create threads.
 */
void	draw_weapon(t_doom *doom)
{
	int				y;
	t_weapon_thread	thread[NB_WEAPON_THREADS];

	y = 0;
	thread[y].dst = doom->surface;
	thread[y].src = &doom->weapon[doom->player.equipped]
		.bxpm[doom->weapon[doom->player.equipped].frame];
	init_first_weapon_thread(doom, &thread[y]);
	tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	while (++y < NB_WEAPON_THREADS)
	{
		thread[y].src = thread[y - 1].src;
		thread[y].sx1 = thread[y - 1].sx1;
		thread[y].sy1 = thread[y - 1].sy2;
		thread[y].sx2 = thread[y - 1].sx2;
		thread[y].sy2 = thread[y].sy1 + thread[y].src->h / NB_WEAPON_THREADS;
		thread[y].dst = thread[y - 1].dst;
		thread[y].dx1 = thread[y - 1].dx1;
		thread[y].dy1 = thread[y - 1].dy2;
		thread[y].dx2 = thread[y - 1].dx2;
		thread[y].dy2 = thread[y].dy1 + thread[y].src->h / NB_WEAPON_THREADS;
		tpool_add(&doom->tpool, weapon_thread, &thread[y]);
	}
	tpool_wait(&doom->tpool);
}
