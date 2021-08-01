/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:25:19 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 15:21:40 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBM_H
# define LIBM_H

# include <math.h>
# define CONVERT_TO_RADIANS	0.0174532925199432955
# define CONVERT_TO_DEGREES	57.295779513082322864

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_v2
{
	double			x;
	double			y;
}					t_v2;

typedef struct s_v3
{	
	double			x;
	double			y;
	double			z;
}					t_v3;

typedef struct s_v4
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_v4;

typedef struct s_rect
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				w;
	int				h;
	double			ratio;
}					t_rect;

/* File: math1.c */
t_point				new_point(int x, int y);
t_v2				new_v2(double x, double y);
t_v3				new_v3(double x, double y, double z);
t_rect				rect_xy2(int x1, int y1, int x2, int y2);
t_rect				rect_xywh(int x1, int y1, int w, int h);
/* File: math2.c */
int					comp_v3(t_v3 v1, t_v3 v2);
t_v3				add_v3(t_v3 v1, t_v3 v2);
t_v3				sub_v3(t_v3 v1, t_v3 v2);
t_v3				mult_v3(t_v3 vec, float scalar);
t_v3				div_v3(t_v3 vec, float scalar);
/* File: math3.c */
int					intersect_check_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
double				point_distance_v3(t_v3 p1, t_v3 p2);
t_v3				closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int					point_on_segment_v2(t_v3 p, t_v3 v1,
						t_v3 v2, double buffer);
t_v3				get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2);
/* File: math4.c */
double				vector_magnitude_v2(t_v3 v);
double				vector_magnitude_v3(t_v3 v);
double				pythagoras(double x, double y);
double				space_diagonal(t_v3 v);
t_v3				normalize(t_v3 vec);
/* File: math5.c */
double				dot_product_v2(t_v3 v1, t_v3 v2);
double				dot_product_v3(t_v3 v1, t_v3 v2);
double				vectors_angle(t_v3 v1, t_v3 v2);
double				cross_product_v2(double x1, double y1,
						double x2, double y2);
t_v3				cross_product_v3(t_v3 v1, t_v3 v2);
/* File: math6.c */
void				get_polar_cordinates(double len, double angle, t_v2 *polar);
void				get_cartesian_cordinates(double x, double y,
						double *len, double *angle);
float				to_radians(float degrees);
float				to_degrees(float radians);
/* File: math7.c */
double				angle_to_point_v2(t_v3 p1, t_v3 p2);
int					ft_sign(double x);
double				point_side_v2(t_v3 v1, t_v3 v2, t_v3 p);
double				point_distance_v2(double x1, double y1,
						double x2, double y2);
/* File: math8.c */
int					cohen_sutherland(t_point v[2], t_rect size);
/* File: math9.c */
void				clamp_radians(double *angle);
void				clamp_degrees(double *angle);

#endif
