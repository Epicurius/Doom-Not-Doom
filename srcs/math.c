/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:44:46 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/03 11:11:56 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//		Set p1 angle to p2 (DEGREES)
double		angle_to_point(t_xyz p1, t_xyz p2)
{
	double angle;
	
	angle = atan2(p2.y - p1.y, p2.x - p1.x) * CONVERT_DEGREES;
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return (angle);
}

//		Space Diagonal
double		space_diagonal(double x, double y, double z)
{
	return (sqrt(x * x + y * y + z * z));
}

//		Make new t_rect struct for texture sheets
t_rect		rect_xy2(int x1, int y1, int x2, int y2)
{
	t_rect new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x2;
	new.y2 = y2;
	new.w = new.x2 - new.x1;
	new.h = new.y2 - new.y1;
	new.ratio = (double)new.h / (double)new.w;
	return (new);
}

t_rect		rect_xywh(int x1, int y1, int w, int h)
{
	t_rect new;

	new.x1 = x1;
	new.y1 = y1;
	new.x2 = x1 + w;
	new.y2 = y1 + h;
	new.w = w;
	new.h = h;
	new.ratio = (double)new.h / (double)new.w;
	return (new);
}

//	Clamp point x,y to rectagle border
void	rect_clamp(int cx, int cy, int rw, int rh, int *x, int *y)
{
	*x = *x - cx;
	*y = *y - cy;
	if (abs(*x) * rh <= abs(*y) * rw)
	{
		*x = cx + rw / 2 * *x / abs(*y);
		*y = cy + sign(*y) * rh / 2;
	}
	else
	{
		*y = cy + rw / 2 * *y / abs(*x);
		*x = cx + sign(*x) * rw / 2;

	}
}

//	Return sign
int	sign(double x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

//https://www.geeksforgeeks.org/program-dot-product-cross-product-two-vector/
double	dot_product(double x0, double y0, double x1, double y1)
{
	return (x0 * x1 + y0 * y1);
}

//	Vectors cross product
double	vxs(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

//	Make a new t_xyz struct and assign values
t_xyz	xyz(double x, double y, double z)
{
	t_xyz new;
	
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

//	Determine whether the two number ranges overlap.
int	overlap(double a0, double a1, double b0, double b1)
{
	if (ft_min(a0, a1) <= ft_max(b0, b1) &&
		ft_min(b0, b1) <= ft_max(a0, a1))
		return (1);
	return (0);
}
//	Determine whether two 2D-boxes intersect. (d is change on p)
int	intersect_box(t_xyz p, t_xyz d, t_xyz vert1, t_xyz vert2)
{
	if (overlap(p.x, (p.x + d.x), vert1.x, vert2.x) &&
		overlap(p.y, (p.y + d.y), vert1.y, vert2.y))
		return (1);
	return (0);
}

//	Determine which side of a line the point is on. Return value: <0, =0 or >0.
double	point_side(t_xyz a, t_xyz b, t_xyz p)
{
	return (vxs(b.x - a.x, b.y - a.y, p.x - a.x, p.y - a.y));
}

//	Calculate point of intersection between 2 lines.
t_xyz	get_intersection(t_xyz a1, t_xyz a2, t_xyz b1, t_xyz b2)
{
	t_xyz		point;
	double		vxs_a;
	double		vxs_b;
	double		div;

	div	=	vxs(a1.x - a2.x, a1.y - a2.y, b1.x - b2.x, b1.y - b2.y);
	vxs_a	=	vxs(a1.x, a1.y, a2.x, a2.y);
	vxs_b	=	vxs(b1.x, b1.y, b2.x, b2.y);
	point.x =	vxs(vxs_a, a1.x - a2.x, vxs_b, b1.x - b2.x) / div;
	point.y =	vxs(vxs_a, a1.y - a2.y, vxs_b, b1.y - b2.y) / div;
	point.z =	0;
	return (point);
}


//	Determine which side of a line the point is on. Return value: <0, =0 or >0.
int	direction_point(t_xyz s1, t_xyz s2, t_xyz p)
{
	double	cross_product;

	s2.x -= s1.x;
	s2.y -= s1.y;
	p.x -= s1.x;
	p.y -= s1.y;
	cross_product = s2.x * p.y - s2.y * p.x;
	if (cross_product > 0)
		return (1);
	if (cross_product < 0)
		return (-1);
	return (0);
}

//	Checks if line intersects
int	intersect_check(t_xyz w1, t_xyz w2, t_xyz p1, t_xyz p2)
{
	int p1_direction;
	int p2_direction;
	int w1_direction;
	int w2_direction;

	p1_direction = direction_point(w1, w2, p1);
	p2_direction = direction_point(w1, w2, p2);
	w1_direction = direction_point(p1, p2, w1);
	w2_direction = direction_point(p1, p2, w2);
	if ((p1_direction == 0 || p1_direction == -1 * p2_direction) &&
		(w1_direction == 0 || w1_direction == -1 * w2_direction))
		return (1);
	return (0);
}
//pythagoras
//	Distance between 2 2d points
double	point_distance_2d(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

//	Distance between 2 3d points
double	point_distance_3d(t_xyz p1, t_xyz p2)
{
	t_xyz square;

	square.x = (p2.x - p1.x) * (p2.x - p1.x);
	square.y = (p2.y - p1.y) * (p2.y - p1.y);
	square.z = (p2.z - p1.z) * (p2.z - p1.z);
	return (sqrt(square.x + square.y + square.z));
}

//	Closest point on a segment to a external point
t_xyz	closest_point_on_segment_2d(t_xyz p, t_xyz a, t_xyz b)
{
	t_xyz	ab;
	t_xyz	ap;
	t_xyz	point;
	double	len;
	double	t;

	ap.x = p.x - a.x;
	ap.y = p.y - a.y;
	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	len = ab.x * ab.x + ab.y * ab.y;
	t = (ap.x * ab.x + ap.y * ab.y) / len;
	t = ft_clamp(t, 0, 1);
	point.x = a.x + t * ab.x;
	point.y = a.y + t * ab.y;
	return (point);
}

//	Is point on segment, optional buffer;
int	point_on_segment_2d(t_xyz p, t_xyz v1, t_xyz v2, double buffer)
{
	double	pv1;
	double	pv2;
	double	len;

	pv1 = point_distance_2d(p.x, p.y, v1.x, v1.y);
	pv2 = point_distance_2d(p.x, p.y, v2.x, v2.y);
	len = point_distance_2d(v1.x, v1.y, v2.x, v2.y);
	if (pv1 + pv2 >= len - buffer && pv1 + pv2 <= len + buffer)
		return (1);
	return (0);
}

int	compare_xyz(t_xyz a, t_xyz b)
{
	if (a.x == b.x && a.y == b.y && a.z == b.z)
		return (1);
	return (0);
}

int	compare_xy(t_xyz a, t_xyz b)
{
	if (a.x == b.x && a.y == b.y)
		return (1);
	return (0);
}

t_xyz	sum_xyz(t_xyz a, t_xyz b)
{
	t_xyz total;

	total.x = a.x + b.x;
	total.y = a.y + b.y;
	total.z = a.z + b.z;
	return (total);	
}
