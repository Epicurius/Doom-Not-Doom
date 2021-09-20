/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:25:19 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/20 11:27:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBM_H
# define LIBM_H

# define TEMP_DOUBLE	float

# include <math.h>
# include "libpf.h"

# define CONVERT_TO_RADIANS	0.0174532925199432955
# define CONVERT_TO_DEGREES	57.295779513082322864

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_v2
{
	float			x;
	float			y;
}					t_v2;

typedef struct s_v3
{	
	float			x;
	float			y;
	float			z;
}					t_v3;

typedef struct s_rect
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				w;
	int				h;
	float			ratio;
}					t_rect;

/* File: Math/math1.c */
t_point				new_point(int x, int y);
t_v2				new_v2(float x, float y);
t_v3				new_v3(float x, float y, float z);
t_rect				rect_xy2(int x1, int y1, int x2, int y2);
t_rect				rect_xywh(int x1, int y1, int w, int h);
/* File: Math/math2.c */
int					comp_v3(t_v3 v1, t_v3 v2);
t_v3				add_v3(t_v3 v1, t_v3 v2);
t_v3				sub_v3(t_v3 v1, t_v3 v2);
t_v3				mult_v3(t_v3 vec, float scalar);
t_v3				div_v3(t_v3 vec, float scalar);
/* File: Math/math3.c */
int					intersect_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
float				point_distance_v3(t_v3 p1, t_v3 p2);
t_v3				closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int					point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, float buff);
t_v3				get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2);
/* File: Math/math4.c */
float				vector_magnitude_v2(t_v3 v);
float				vector_magnitude_v3(t_v3 v);
float				pythagoras(float x, float y);
float				space_diagonal(t_v3 v);
float				normalize_v3(t_v3 *vec);
/* File: Math/math5.c */
float				dot_product_v2(t_v3 v1, t_v3 v2);
float				dot_product_v3(t_v3 v1, t_v3 v2);
float				vectors_angle(t_v3 v1, t_v3 v2);
float				cross_product_v2(float x1, float y1,
						float x2, float y2);
t_v3				cross_product_v3(t_v3 v1, t_v3 v2);
/* File: Math/math6.c */
void				get_polar_coordinates(float len, float angle, t_v2 *polar);
void				get_cartesian_coordinates(float x, float y,
						float *len, float *angle);
float				to_radians(float degrees);
float				to_degrees(float radians);
/* File: Math/math7.c */
float				degree_to_point_v2(t_v3 p1, t_v3 p2);
int					ft_sign(float x);
float				point_side_v2(t_v3 v1, t_v3 v2, t_v3 p);
float				point_distance_v2(float x1, float y1,
						float x2, float y2);
/* File: Math/math8.c */
int					cohen_sutherland(t_point v[2], t_rect size);
/* File: Math/math9.c */
void				clamp_radians(double *angle);
void				clamp_degrees(double *angle);
/* File: Math/math10.c */
void				print_v2(char *str, t_v2 v);
void				print_v3(char *str, t_v3 v);

#endif
