/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/08/01 13:41:44 nneronin
 * Updated: 2021/09/20 10:28:15 nneronin
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
