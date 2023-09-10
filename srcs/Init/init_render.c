/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

void	init_render(t_doom *doom)
{
	int	i;

	i = -1;
	doom->sectbool = protalloc(sizeof(char) * doom->nb.sectors);
	doom->render = protalloc(sizeof(t_render) * doom->nb.threads);
	doom->zbuffer = protalloc(sizeof(float)
			* (doom->surface->w * doom->surface->h));
	doom->surface->userdata = doom->zbuffer;
	while (++i < doom->nb.threads)
	{
		doom->render[i].surface = doom->surface;
		doom->render[i].sectors = doom->sectors;
		doom->render[i].nb_sectors = doom->nb.sectors;
		doom->render[i].skybox = doom->skybox;
		doom->render[i].mtx = doom->mtx;
		doom->render[i].stx = doom->stx;
		doom->render[i].center = doom->c;
		doom->render[i].player = &doom->player;
		doom->render[i].cam = &doom->cam;
	}
}
