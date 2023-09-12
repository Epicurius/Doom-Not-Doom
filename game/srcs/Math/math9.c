/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libm.h"

/*
 *	Clamp radians between degrees 0 -> 360.
 */
void	clamp_radians(double *angle)
{
	*angle *= CONVERT_TO_DEGREES;
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
	*angle *= CONVERT_TO_RADIANS;
}

/*
 *	Clamp degrees between 0 -> 360.
 */
void	clamp_degrees(double *angle)
{
	while (*angle > 360)
		*angle -= 360;
	while (*angle < 0)
		*angle += 360;
}
