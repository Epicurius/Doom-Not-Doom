/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:50:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/23 15:06:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	in_sector(t_sector *sector, t_v3 pos)
{
	int		i;
	double	p;

	i = -1;
	if (get_floor_at_pos(sector, pos) > pos.z
		|| get_ceiling_at_pos(sector, pos) < pos.z)
		return (0);
	while (++i < sector->npoints)
	{
		if (point_side_v2(sector->wall[i]->v1, sector->wall[i]->v2, pos) < 0)
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
