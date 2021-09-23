/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:39 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/23 11:16:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_render(t_doom *doom)
{
	int	i;

	i = -1;
	doom->sectbool = PROT_ALLOC(sizeof(char) * doom->nb.sectors);
	doom->render = PROT_ALLOC(sizeof(t_render) * doom->nb.threads);
	doom->zbuffer = PROT_ALLOC(sizeof(float)
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
