/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 17:08:48 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/03 13:56:10 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

static inline int	check_line_intersect(float p0, float p1,
	float *t0, float *t1)
{
	float	r;

	r = p1 / p0;
	if (p0 == 0 && p1 < 0)
		return (FALSE);
	if (p0 < 0)
	{
		if (r > *t1)
			return (FALSE);
		else if (r > *t0)
			*t0 = r;
	}
	else if (p0 > 0)
	{
		if (r < *t0)
			return (FALSE);
		else if (r < *t1)
			*t1 = r;
	}
	return (TRUE);
}

int	liang_barsky(t_rect size, t_point *line)
{
	float	t0;
	float	t1;
	t_v2	delta;

	t0 = 0.0;
	t1 = 1.0;
	delta.x = line[0].x - line[1].x;
	delta.y = line[0].y - line[1].y;
	if (!check_line_intersect(-delta.x, -(size.x1 - line[1].x), &t0, &t1))
		return (FALSE);
	if (!check_line_intersect(delta.x, size.x2 - line[1].x, &t0, &t1))
		return (FALSE);
	if (!check_line_intersect(-delta.y, -(size.y1 - line[1].y), &t0, &t1))
		return (FALSE);
	if (!check_line_intersect(delta.y, size.y2 - line[1].y, &t0, &t1))
		return (FALSE);
	line[0] = new_point(line[1].x + t0 * delta.x, line[1].y + t0 * delta.y);
	line[1] = new_point(line[1].x + t1 * delta.x, line[1].y + t1 * delta.y);
	return (1);
}
