/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 17:38:47 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/31 11:26:26 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libm.h"

//		Set p1 angle to p2 (DEGREES)
double	angle_to_point_v2(t_v3 p1, t_v3 p2)
{
	double	angle;

	angle = atan2(p2.y - p1.y, p2.x - p1.x) * CONVERT_DEGREES;
	while (angle > 360)
		angle -= 360;
	while (angle < 0)
		angle += 360;
	return (angle);
}

//	Return sign
int	ft_sign(double x)
{
	if (x > 0)
		return (1);
	if (x < 0)
		return (-1);
	return (0);
}

//	Determine which side of a line the point is on. Return value: <0, =0 or >0.
double	point_side_v2(t_v3 v1, t_v3 v2, t_v3 p)
{
	return ((v2.x - v1.x) * (p.y - v1.y) - (v2.y - v1.y) * (p.x - v1.x));
}

//	Distance between 2 2d points
double	point_distance_v2(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	print_v2(char *str, t_v2 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f]\n", v.x, v.y);
}

void	print_v3(char *str, t_v3 v)
{
	if (str)
		ft_printf("%s\t", str);
	ft_printf("[%.2f\t%.2f\t%.2f]\n", v.x, v.y, v.z);
}
