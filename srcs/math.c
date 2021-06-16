/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 12:44:46 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/16 17:49:36 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

//		Set p1 angle to p2 (DEGREES)

double		angle_to_point(t_v3 p1, t_v3 p2)
{
	double angle;
	
	angle = atan2(p2.y - p1.y, p2.x - p1.x) * CONVERT_DEGREES;
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return (angle);
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

//	Vectors cross product 2v
double	vxs(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

//	Make a new t_v3 struct and assign values
t_v3	xyz(double x, double y, double z)
{
	t_v3 new;
	
	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

//	Calculate point of intersection between 2 lines.
t_v3	get_intersection(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2)
{
	t_v3		point;
	double		div;
	double		vxs_a;
	double		vxs_b;

	div		=	vxs(a1.x - a2.x, a1.y - a2.y, b1.x - b2.x, b1.y - b2.y);
	vxs_a	=	vxs(a1.x, a1.y, a2.x, a2.y);
	vxs_b	=	vxs(b1.x, b1.y, b2.x, b2.y);
	point.x =	vxs(vxs_a, a1.x - a2.x, vxs_b, b1.x - b2.x) / div;
	point.y =	vxs(vxs_a, a1.y - a2.y, vxs_b, b1.y - b2.y) / div;
	point.z =	0;
	return (point);
}

/* ---------------------------------------------------------------------------------------- */
//		Length of a vector 2D
double	vector_magnitude_2D(t_v3 v)
{
	return (sqrt((v.x * v.y) + (v.x * v.y)));
}

//		Length of a vector 3D
double	vector_magnitude(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

//		Space Diagonal
double	pythagoras(double x, double y)
{
	return (sqrt(x * x + y * y));
}

//		Space Diagonal/Pythagoras
double	space_diagonal(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

//		Get normal
t_v3	normalize(t_v3 vec)
{
	float	length;

	length = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return (xyz(vec.x / length, vec.y / length, vec.z / length));
}

//		Return scalar
double	dot_product_2D(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

double	dot_product(t_v3 v1, t_v3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

//		Returns Radians
double	vectors_angle(t_v3 v1, t_v3 v2)
{
	return (acos(dot_product(v1, v2) / (space_diagonal(v1) * space_diagonal(v2))));
}

t_v3	cross_product(t_v3 v1, t_v3 v2)
{
	t_v3 res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

int	comp_vec(t_v3 v1, t_v3 v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (1);
	return (0);
}

t_v3	add_vec(t_v3 v1, t_v3 v2)
{
	return (xyz(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_v3	sub_vec(t_v3 v1, t_v3 v2)
{
	return (xyz(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_v3	mult_vec(t_v3 vec, float scalar)
{
	return (xyz(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

//		x,y of vector
t_v3	get_polar_cordinates(double len, double angle)
{
	return (xyz(len * cos(angle), len * sin(angle), 0));
}

//		len, angle of vector
void	get_cartesian_cordinates(double x, double y, double *len, double *angle)
{
	*len = sqrt(x * x + y * y);
	*angle = atan(y / x);
}

//		Deprecated, use #define RADIANS_CONVERT
float	to_radians(float degrees)
{
	return (degrees * ((float)M_PI / 180.0f));
}

//		Deprecated, use #define DEGREES1_CONVERT
float	to_degrees(float radians)
{
	return (radians * (180.0f / (float)M_PI));
}

//	Determine whether the two number ranges overlap.
int	overlap(double a0, double a1, double b0, double b1)
{
	if (ft_min(a0, a1) <= ft_max(b0, b1) && ft_min(b0, b1) <= ft_max(a0, a1))
		return (1);
	return (0);
}

//	Determine which side of a line the point is on. Return value: <0, =0 or >0.
double	point_side(t_v3 v1, t_v3 v2, t_v3 p)
{
	return ((v2.x - v1.x) * (p.y - v1.y) - (v2.y - v1.y) * (p.x - v1.x));
}

//	Checks if line intersects
int	intersect_check(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2)
{
	int p1_dir;
	int w1_dir;

	p1_dir = sign(point_side(w1, w2, p1));
	w1_dir = sign(point_side(p1, p2, w1));
	if ((p1_dir == 0 || p1_dir == -1 * sign(point_side(w1, w2, p2)))
		&& (w1_dir == 0 || w1_dir == -1 * sign(point_side(p1, p2, w2))))
		return (1);
	return (0);
}

//	Distance between 2 2d points
double	point_distance_2d(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

//	Distance between 2 3d points
double	point_distance_3d(t_v3 p1, t_v3 p2)
{
	t_v3 square;

	square.x = (p2.x - p1.x) * (p2.x - p1.x);
	square.y = (p2.y - p1.y) * (p2.y - p1.y);
	square.z = (p2.z - p1.z) * (p2.z - p1.z);
	return (sqrt(square.x + square.y + square.z));
}

//	Closest point on a segment to a external point
t_v3	closest_point_on_segment_2d(t_v3 p, t_v3 a, t_v3 b)
{
	t_v2	ab;
	t_v3	point;
	double	len;
	double	t;

	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	len = ab.x * ab.x + ab.y * ab.y;
	t = ((p.x - a.x) * ab.x + (p.y - a.x) * ab.y) / len;
	t = ft_clamp(t, 0, 1);
	point.x = a.x + t * ab.x;
	point.y = a.y + t * ab.y;
	return (point);
}


//	Is point on segment, optional buffer;
int	point_on_segment_2d(t_v3 p, t_v3 v1, t_v3 v2, double buffer)
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