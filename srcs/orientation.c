
#include "doom.h"
/*
int	orientation(t_xyz p1, t_xyz p2, double yaw)
{
	double angle;
	double z;
	double x;
	int i;
	
	i = 0;
	z = p1.y - p2.y;
	x = p1.x - p2.x;
	yaw -= 22.5;
	angle = (int)((atan2(z, x)) * CONVERT_DEGREES) % 360;
	if (yaw < 0)
		yaw += 360;
	if (angle < 0)
		angle += 360;
	while (!(angle >= yaw + i * 45 && angle < yaw + (i + 1) * 45))
	{
		if (angle < yaw - i * 45 && angle >= yaw - (i + 1) * 45)
			return (7 - i);
		i++;
	}
	return (i);
}*/

void	degree_fix(double *degrees)
{
	while (*degrees > 360)
		*degrees -= 360;
	while (*degrees <= 0)
		*degrees += 360;
}

int	orientation(t_xyz p1, t_xyz p2, double yaw, int nb_angles)
{
	double angle;
	double a;
	int i;

	if (nb_angles <= 1)
		return (0);	
	angle = (int)((atan2(p1.y - p2.y, p1.x - p2.x))
			* CONVERT_DEGREES) % 360;
	a = 360 / nb_angles;
	yaw -= a / 2;
	degree_fix(&yaw);
	degree_fix(&angle);
	i = 0;
	while (!(angle >= yaw + i * a && angle < yaw + (i + 1) * a))
	{
		if (angle < yaw - i * a && angle >= yaw - (i + 1) * a)
			return (nb_angles - 1 - i);
		i++;
	}
	return (i);
}
