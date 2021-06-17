/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:25:19 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 15:47:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_v2
{
	double		x;
	double		y;
}				t_v2;

typedef struct s_v3
{
	double		x;
	double		y;
	double		z;
}				t_v3;

typedef struct s_v4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_v4;

typedef struct	s_rect
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			w;
	int			h;
	double		ratio;
}				t_rect;

double		angle_to_point_v2(t_v3 p1, t_v3 p2);
t_rect		rect_xy2(int x1, int y1, int x2, int y2);
t_rect		rect_xywh(int x1, int y1, int w, int h);
void	rect_clamp(int cx, int cy, int rw, int rh, int *x, int *y);
int	ft_sign(double x);
t_point	new_point(int x, int y);
t_v2	new_v2(double x, double y);
t_v3	new_v3(double x, double y, double z);
t_v4	new_v4(double x, double y, double z, double w);
double	vector_magnitude_v2(t_v3 v);
double	vector_magnitude_v3(t_v3 v);
double	pythagoras(double x, double y);
double	space_diagonal(t_v3 v);
t_v3	normalize(t_v3 vec);
double	dot_product_v2(t_v3 v1, t_v3 v2);
double	dot_product_v3(t_v3 v1, t_v3 v2);
double	vectors_angle(t_v3 v1, t_v3 v2);
double	cross_product_v2(double x1, double y1, double x2, double y2);
t_v3	cross_product_v3(t_v3 v1, t_v3 v2);
int	comp_v3(t_v3 v1, t_v3 v2);
t_v3	add_v3(t_v3 v1, t_v3 v2);
t_v3	sub_v3(t_v3 v1, t_v3 v2);
t_v3	mult_v3(t_v3 vec, float scalar);
void	get_polar_cordinates(double len, double angle, t_v2 *polar);
void	get_cartesian_cordinates(double x, double y, double *len, double *angle);
float	to_radians(float degrees);
float	to_degrees(float radians);
int	nb_overlap(double a0, double a1, double b0, double b1);
double	point_side_v2(t_v3 v1, t_v3 v2, t_v3 p);
int	intersect_check_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
double	point_distance_v2(double x1, double y1, double x2, double y2);
double	point_distance_v3(t_v3 p1, t_v3 p2);
t_v3	closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int	point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, double buffer);
t_v3	get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2);
