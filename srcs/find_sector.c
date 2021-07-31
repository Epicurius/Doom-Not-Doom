/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:50:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/31 10:09:21 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	in_sector(t_sector *sector, t_v3 pos)
{
	int		i;

	i = -1;
	if (floor_at(sector, pos) > pos.z
		|| ceiling_at(sector, pos) < pos.z)
		return (0);
	while (++i < sector->npoints)
	{
		if (point_side_v2(sector->wall[i]->v1, sector->wall[i]->v2, pos) < 0.0f)
			return (0);
	}
	return (1);
}

int	find_sector(t_sector *sectors, int nb, t_v3 pos)
{
	int	i;

	i = -1;
	while (++i < nb)
	{
		if (in_sector(&sectors[i], pos))
			return (i);
	}
	return (-1);
}
