/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 10:42:25 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/11 15:27:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

/*	Cohen Sutherland clipping line in rectangle algorithm */
static unsigned int	compute_outcode(int x, int y, t_rect size)
{
	unsigned int	i;

	i = 0;
	if (y > size.y2)
		i |= 0x1;
	else if (y < size.y1)
		i |= 0x2;
	if (x > size.x2)
		i |= 0x4;
	else if (x < size.x1)
		i |= 0x8;
	return (i);
}

static unsigned int	cohen_sutherland2(t_point *v, t_rect size, t_v3 i)
{
	unsigned int	outcode;

	v->x = i.x;
	v->y = i.y;
	outcode = compute_outcode(v->x, v->y, size);
	return (outcode);
}

static void	cohen_sutherland1(t_point *v, t_rect size,
		unsigned int outcode_ex, t_v3 *i)
{
	if (outcode_ex & 0x1)
	{
		i->x = v[0].x + (v[1].x - v[0].x)
			* (size.y2 - v[0].y) / (v[1].y - v[0].y);
		i->y = size.y2;
	}
	else if (outcode_ex & 0x2)
	{
		i->x = v[0].x + (v[1].x - v[0].x)
			* (size.y1 - v[0].y) / (v[1].y - v[0].y);
		i->y = size.y1;
	}
	else if (outcode_ex & 0x4)
	{
		i->y = v[0].y + (v[1].y - v[0].y)
			* (size.x2 - v[0].x) / (v[1].x - v[0].x);
		i->x = size.x2;
	}
	else
	{
		i->y = v[0].y + (v[1].y - v[0].y)
			* (size.x1 - v[0].x) / (v[1].x - v[0].x);
		i->x = size.x1;
	}
}

int	cohen_sutherland(t_point v[2], t_rect size)
{
	t_v3			i;
	unsigned int	outcode_ex;
	unsigned int	outcode_v1;
	unsigned int	outcode_v2;

	outcode_v1 = compute_outcode(v[0].x, v[0].y, size);
	outcode_v2 = compute_outcode(v[1].x, v[1].y, size);
	if (outcode_v1 & outcode_v2)
		return (0);
	while (1)
	{
		if (outcode_v1 == 0 && outcode_v2 == 0)
			return (1);
		else
		{
			outcode_ex = outcode_v2;
			if (outcode_v1)
				outcode_ex = outcode_v1;
			cohen_sutherland1(v, size, outcode_ex, &i);
			if (outcode_ex == outcode_v1)
				outcode_v1 = cohen_sutherland2(&v[0], size, i);
			else
				outcode_v2 = cohen_sutherland2(&v[1], size, i);
		}
	}
}
