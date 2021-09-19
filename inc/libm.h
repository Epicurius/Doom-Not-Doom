/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:25:19 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/19 17:30:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBM_H
# define LIBM_H

# define TEMP_DOUBLE	double

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
	TEMP_DOUBLE			x;
	TEMP_DOUBLE			y;
}					t_v2;

typedef struct s_v3
{	
	TEMP_DOUBLE			x;
	TEMP_DOUBLE			y;
	TEMP_DOUBLE			z;
}					t_v3;

typedef struct s_rect
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				w;
	int				h;
	TEMP_DOUBLE			ratio;
}					t_rect;

/* File: Math/math1.c */
t_point				new_point(int x, int y);
t_v2				new_v2(TEMP_DOUBLE x, TEMP_DOUBLE y);
t_v3				new_v3(TEMP_DOUBLE x, TEMP_DOUBLE y, TEMP_DOUBLE z);
t_rect				rect_xy2(int x1, int y1, int x2, int y2);
t_rect				rect_xywh(int x1, int y1, int w, int h);
/* File: Math/math2.c */
int					comp_v3(t_v3 v1, t_v3 v2);
t_v3				add_v3(t_v3 v1, t_v3 v2);
t_v3				sub_v3(t_v3 v1, t_v3 v2);
t_v3				mult_v3(t_v3 vec, TEMP_DOUBLE scalar);
t_v3				div_v3(t_v3 vec, TEMP_DOUBLE scalar);
/* File: Math/math3.c */
int					intersect_v2(t_v3 w1, t_v3 w2, t_v3 p1, t_v3 p2);
TEMP_DOUBLE				point_distance_v3(t_v3 p1, t_v3 p2);
t_v3				closest_point_on_segment_v2(t_v3 p, t_v3 a, t_v3 b);
int					point_on_segment_v2(t_v3 p, t_v3 v1, t_v3 v2, TEMP_DOUBLE buff);
t_v3				get_intersection_v2(t_v3 a1, t_v3 a2, t_v3 b1, t_v3 b2);
/* File: Math/math4.c */
TEMP_DOUBLE				vector_magnitude_v2(t_v3 v);
TEMP_DOUBLE				vector_magnitude_v3(t_v3 v);
TEMP_DOUBLE				pythagoras(TEMP_DOUBLE x, TEMP_DOUBLE y);
TEMP_DOUBLE				space_diagonal(t_v3 v);
TEMP_DOUBLE				normalize_v3(t_v3 *vec);
/* File: Math/math5.c */
TEMP_DOUBLE				dot_product_v2(t_v3 v1, t_v3 v2);
TEMP_DOUBLE				dot_product_v3(t_v3 v1, t_v3 v2);
TEMP_DOUBLE				vectors_angle(t_v3 v1, t_v3 v2);
TEMP_DOUBLE				cross_product_v2(TEMP_DOUBLE x1, TEMP_DOUBLE y1,
						TEMP_DOUBLE x2, TEMP_DOUBLE y2);
t_v3				cross_product_v3(t_v3 v1, t_v3 v2);
/* File: Math/math6.c */
void				get_polar_coordinates(TEMP_DOUBLE len, TEMP_DOUBLE angle, t_v2 *polar);
void				get_cartesian_coordinates(TEMP_DOUBLE x, TEMP_DOUBLE y,
						TEMP_DOUBLE *len, TEMP_DOUBLE *angle);
TEMP_DOUBLE				to_radians(TEMP_DOUBLE degrees);
TEMP_DOUBLE				to_degrees(TEMP_DOUBLE radians);
/* File: Math/math7.c */
TEMP_DOUBLE				angle_to_point_v2(t_v3 p1, t_v3 p2);
int					ft_sign(TEMP_DOUBLE x);
TEMP_DOUBLE				point_side_v2(t_v3 v1, t_v3 v2, t_v3 p);
TEMP_DOUBLE				point_distance_v2(TEMP_DOUBLE x1, TEMP_DOUBLE y1,
						TEMP_DOUBLE x2, TEMP_DOUBLE y2);
/* File: Math/math8.c */
int					cohen_sutherland(t_point v[2], t_rect size);
/* File: Math/math9.c */
void				clamp_radians(TEMP_DOUBLE *angle);
void				clamp_degrees(TEMP_DOUBLE *angle);
/* File: Math/math10.c */
void				print_v2(char *str, t_v2 v);
void				print_v3(char *str, t_v3 v);

#endif
