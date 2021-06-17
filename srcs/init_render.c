/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:51:39 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 12:28:57 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_render(t_doom *doom)
{
	int	x;

	x = -1;
	doom->fustrum = ft_pmalloc(sizeof(int)
			* doom->surface->w, "doom->fustrum");
	doom->render = ft_pmalloc(sizeof(t_render)
			* doom->nb.threads, "doom->render");
	doom->zbuffer = ft_pmalloc(sizeof(double)
			* (doom->surface->w * doom->surface->h), "doom->zbuffer");
	doom->surface->userdata = doom->zbuffer;
	while (++x < doom->nb.threads)
	{
		doom->render[x].surface = doom->surface;
		doom->render[x].sectors = doom->sectors;
		doom->render[x].fustrum = doom->fustrum;
		doom->render[x].skybox = doom->skybox;
		doom->render[x].mtx = doom->mtx;
		doom->render[x].stx = doom->stx;
	}
}
