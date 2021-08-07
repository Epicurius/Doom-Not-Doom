/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_corners.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 17:18:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/07 13:03:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	init_corners(t_doom *doom)
{
	int	i;
	int	j;

	i = -1;
	while (++i < doom->nb.walls)
	{
		if (doom->walls[i].solid || doom->walls[i].n == -1)
		{
			doom->walls[i].v1.z = 1.0f;
			doom->walls[i].v2.z = 1.0f;
			j = -1;
			while (++j < doom->nb.walls)
			{
				if (doom->walls[i].v1.x == doom->walls[j].v1.x
					&& doom->walls[i].v1.y == doom->walls[j].v1.y)
					doom->walls[j].v1.z = 1.0f;
				if (doom->walls[i].v2.x == doom->walls[j].v2.x
					&& doom->walls[i].v2.y == doom->walls[j].v2.y)
					doom->walls[j].v2.z = 1.0f;
			}
		}
	}
}
