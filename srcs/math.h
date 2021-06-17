/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:25:19 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/17 10:46:43 by nneronin         ###   ########.fr       */
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

double	vector_magnitude_v2(t_v3 v);
double	vector_magnitude_v3(t_v3 v);
double	space_diagonal(t_v3 v);
t_v3	normalize(t_v3 vec);
double	dot_product_v2(t_v3 v1, t_v3 v2);
double	dot_product_v3(t_v3 v1, t_v3 v2);
double	vectors_angle(t_v3 v1, t_v3 v2);
t_v3	cross_product_v3(t_v3 v1, t_v3 v2);
int		comp_v3(t_v3 v1, t_v3 v2);
t_v3	add_v2(t_v3 v1, t_v3 v2);
t_v3	sub_v3(t_v3 v1, t_v3 v2);
t_v3	mult_v3(t_v3 vec, float scalar);
void	get_polar_cordinates(double len, double angle, t_v2 *polar);
void	get_cartesian_cordinates(double x, double y, double *len, double *angle);
float	to_radians(float degrees);
float	to_degrees(float radians);

t_rect		rect_xy2(int x1, int y1, int x2, int y2);
t_rect		rect_xywh(int x1, int y1, int w, int h);
