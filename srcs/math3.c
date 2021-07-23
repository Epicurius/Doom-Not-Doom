/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:36:27 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/23 12:58:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

//	Checks if line intersects
int	intersect_check_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2)
{
	int	p1_dir;
	int	w1_dir;

	p1_dir = ft_sign(point_side_v2(w1, w2, p1));
	w1_dir = ft_sign(point_side_v2(p1, p2, w1));
	if ((p1_dir == 0 || p1_dir == -1 * ft_sign(point_side_v2(w1, w2, p2)))
		&& (w1_dir == 0 || w1_dir == -1 * ft_sign(point_side_v2(p1, p2, w2))))
		return (1);
	return (0);
}

//	Distance between 2 3d points
double	point_distance_v3(t_v3 p1, t_v3 p2)
{
	t_v3	square;

	square.x = (p2.x - p1.x) * (p2.x - p1.x);
	square.y = (p2.y - p1.y) * (p2.y - p1.y);
	square.z = (p2.z - p1.z) * (p2.z - p1.z);
	return (sqrt(square.x + square.y + square.z));
}

//	Closest point on a segment to a external point
t_v3	closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b)
{
	float	l;
	float	t;
	t_v3	point;

	l = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	if (l == 0)
		return (a);
	t = (p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y);
	t = t / l;
	t = t > 1.0 ? 1 : t;
	t = t < 0.0 ? 0 : t;
	point.x = a.x + t * (b.x - a.x);
	point.y = a.y + t * (b.y - a.y);
	return (point);
}

//float sqr(float x)
//{
//	return (x * x);
//}
//
//float dist2(t_v3 v, t_v3 w) { return (sqr(v.x - w.x) + sqr(v.y - w.y)); }
//
//t_v3	closest_point_on_segment_v22(t_v3 p, t_v3 a, t_v3 b)
//{
//  float l2 = dist2(a, b);
//  if (l2 == 0)
//  	return a;
//  float t = ((p.x - a.x) * (b.x - a.x) + (p.y - a.y) * (b.y - a.y)) / l2;
//  //t = max(0, min(1, t));
//  t_v3 asd;
//  asd.x = a.x + t * (b.x - a.x);
//  asd.y = a.y + t * (b.y - a.y);
//  //ft_printf("(%f)\n", dist(p, asd));
//  return asd;
//}

//	Is point on segment, optional buffer;
int	point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, double buffer)
{
	double	pv1;
	double	pv2;
	double	len;

	pv1 = point_distance_v2(p.x, p.y, v1.x, v1.y);
	pv2 = point_distance_v2(p.x, p.y, v2.x, v2.y);
	len = point_distance_v2(v1.x, v1.y, v2.x, v2.y);
	if (pv1 + pv2 >= len - buffer && pv1 + pv2 <= len + buffer)
		return (1);
	return (0);
}

//	Calculate point of intersection between 2 lines.
t_v3	get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2)
{
	t_v3	point;
	double	div;
	double	vxs_a;
	double	vxs_b;

	vxs_a = cross_product_v2(a1.x, a1.y, a2.x, a2.y);
	vxs_b = cross_product_v2(b1.x, b1.y, b2.x, b2.y);
	div = cross_product_v2(a1.x - a2.x, a1.y - a2.y, b1.x - b2.x, b1.y - b2.y);
	point.x = cross_product_v2(vxs_a, a1.x - a2.x, vxs_b, b1.x - b2.x) / div;
	point.y = cross_product_v2(vxs_a, a1.y - a2.y, vxs_b, b1.y - b2.y) / div;
	return (point);
}
