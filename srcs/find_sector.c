/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:50:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/12 10:05:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		in_sector(t_sector *sector, t_xyz pos)
{
	int i;
	double p;

	i = -1;
	while (++i < sector->npoints)
	{
		p = point_side(sector->wall[i]->v1, sector->wall[i]->v2, pos);
		if (p < 0)
			return (0);
	}
	return (1);
}

int		find_sector(t_doom *doom, t_xyz pos)
{
	int	i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		if (in_sector(&doom->sectors[i], pos))
			return (i);
	}
	return (-1);
}
