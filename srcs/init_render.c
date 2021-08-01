/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:39 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 09:07:49 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_render(t_doom *doom)
{
	int	i;

	i = -1;
	doom->render = protalloc(sizeof(t_render)
			* doom->nb.threads, "doom->render");
	doom->zbuffer = protalloc(sizeof(double)
			* (doom->surface->w * doom->surface->h), "doom->zbuffer");
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
	}
}
