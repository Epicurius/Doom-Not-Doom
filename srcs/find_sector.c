
#include "doom.h"

int		find_sector(t_doom *doom, t_xyz e)
{
	int		is;
	int		i;
	int		j;
	int		s;
	t_xyz		*v;

	s = -1;
	is = 0;
	while (++s < SECTORNUM)
	{
		i = 0;
		v = doom->sectors[s].vertex;
		j = doom->sectors[s].npoints - 1;
		while (i < doom->sectors[s].npoints)
		{
			if (((v[i].y > e.y) != (v[j].y > e.y)) &&
				(e.x < (v[j].x - v[i].x) * (e.y - v[i].y) /
					(v[j].y - v[i].y) + v[i].x))
				is = !is;
			j = i++;
		}
		if (is == 1)
			return (s);
	}
	return (-1);
}
