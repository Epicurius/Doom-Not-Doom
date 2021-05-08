/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:50:54 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 10:50:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		find_sector(t_doom *doom, t_xyz e)
{
	int		is;
	int		j;
	int	i;
	int	s;
	t_xyz		v1;
	t_xyz		v2;

	s = -1;
	is = 0;
	while (++s < doom->nb.sectors)
	{
		i = 0;
		j = doom->sectors[s].npoints - 1;
		while (i < doom->sectors[s].npoints)
		{
			v1 = doom->sectors[s].wall[i]->v1;
			v2 = doom->sectors[s].wall[j]->v1;
			if (((v1.y > e.y) != (v2.y > e.y)) &&
				(e.x < (v2.x - v1.x) * (e.y - v1.y) / (v2.y - v1.y) + v1.x))
				is = !is;
			j = i++;
		}
		if (is == 1)
			return (s);
	}
	return (-1);
}
/*
int		in_range(double nb, double val1, double val2)
{
	double min;
	double max;

	min = (val1 <= val2) ? val1 : val2;
	max = (val1 > val2) ? val1 : val2;
	if (nb > min && nb <= max)
		return (1);
	return (0);
}

int		diff_sign(double nb1, double nb2)
{
	if ((nb1 > 0 && nb2 > 0) || (nb1 < 0 && nb2 < 0) || nb1 == 0)
		return (0);
	return (1);
}

double	get_s_pos(t_doom *doom, t_xyz pos, int sector, int i)
{
	double	res;

	res = (pos.x - doom->sectors[sector].wall[i]->v1.x)
	* (doom->sectors[sector].wall[i]->v2.y - doom->sectors[sector].wall[i]->v1.y)
	- (pos.y - doom->sectors[sector].wall[i]->v1.y)
	* (doom->sectors[sector].wall[i]->v2.x - doom->sectors[sector].wall[i]->v1.x);
	return (res);
}

double	get_e_pos(t_doom *doom, t_xyz pos, int sector, int i)
{
	int x;
	double	res;

	res = (doom->sectors[sector].xmax + 1 - doom->sectors[sector].wall[i]->v1.x)
	* (doom->sectors[sector].wall[i]->v2.y - doom->sectors[sector].wall[i]->v1.y)
	- (pos.y - doom->sectors[sector].wall[i]->v1.y)
	* (doom->sectors[sector].wall[i]->v2.x - doom->sectors[sector].wall[i]->v1.x);
	return (res);
}

int		is_in_sector(t_doom *doom, int sector, t_xyz pos)
{
	int		count;
	int		i;
	double	s_pos;
	double	e_pos;

	i = 0;
	count = 0;
	if (sector < 0 || sector >= doom->nb.sectors)
		return (0);
	while (i < doom->sectors[sector].npoints)
	{
		s_pos	= get_s_pos(doom, pos, sector, i);
		e_pos	= get_e_pos(doom, pos, sector, i);
		if (diff_sign(s_pos, e_pos)
			&& in_range(pos.y,	doom->sectors[sector].wall[i]->v1.y,
								doom->sectors[sector].wall[i]->v2.y))
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

int		find_pos_sector(t_doom *doom, t_xyz pos)
{
	int i;

	i = -1;
	while (++i < doom->nb.sectors)
	{
		if (is_in_sector(doom, i, pos))
			return (i);
	}
	return (-1);
}*/
