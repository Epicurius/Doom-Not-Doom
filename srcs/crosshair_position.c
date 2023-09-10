/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

static void	debug(t_render *render, t_wall *wall)
{
	LG_DEBUG("Wall:\t%d Sector: %d Neighbour: %d.",
		wall->id, wall->sect, wall->n);
	LG_DEBUG("Player:\t%d [%.1f][%.1f][%.1f].",
		render->player->sector, render->player->where.x,
		render->player->where.y, render->player->where.z);
}

/*
 *	Checks it the crosshair(center of the surface) is the pixel beeing drawn.
 *	And player is shooting it is saves the position for the bullet hole.
 *	So the next draw loop can draw it.
 *	Works atm only on walls.
 */
void	crosshair_position(t_render *render, t_vline *vline,
			float alpha, int coord)
{
	t_wall		*wall;
	t_wsprite	*bullet_hole;

	if (coord == render->center.z && render->player->action == SHOOTING)
	{
		wall = render->wall;
		if (render->bullet_hole->curr >= MAX_BULLET_HOLES)
			render->bullet_hole->curr = 0;
		bullet_hole = &render->bullet_hole->num[render->bullet_hole->curr];
		bullet_hole->where.x = (vline->alpha / wall->sv2.z)
			/ ((1 - vline->alpha) / wall->sv1.z + vline->alpha / wall->sv2.z)
			* wall->width;
		bullet_hole->where.y = alpha * wall->height;
		bullet_hole->where.x -= 0.5;
		bullet_hole->where.y -= 0.5;
		bullet_hole->ready = FALSE;
		render->bullet_hole->curr += 1;
		if (render->bullet_hole->total < MAX_BULLET_HOLES)
			render->bullet_hole->total += 1;
		if (render->player->debug)
			debug(render, wall);
	}
}
