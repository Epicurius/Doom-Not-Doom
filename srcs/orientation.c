
#include "doom.h"

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
}
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
	angle = (int)((atan2(z, x)) * CONVERT_DEGREES) % 360;
	if (angle < 0)
		angle += 360;
	while (!(angle >= yaw + i && angle < yaw + i + 1))
		i++;
	printf("%f %d\n", angle, i);
	return (i);
}*/
