
#include "doom.h"

int		find_sector(t_doom *doom, t_xyz e)
{
	int		is;
	int		j;
	int	i;
	int	s;
	t_xyz		v1;
	t_xyz		v2;

	s = -1;
	is = 0;
	while (++s < doom->nb.sectors)
	{
		i = 0;
		j = doom->sectors[s].npoints - 1;
		while (i < doom->sectors[s].npoints)
		{
			v1 = doom->sectors[s].wall[i]->v1;
			v2 = doom->sectors[s].wall[j]->v1;
			if (((v1.y > e.y) != (v2.y > e.y)) &&
				(e.x < (v2.x - v1.x) * (e.y - v1.y) / (v2.y - v1.y) + v1.x))
				is = !is;
			j = i++;
		}
		if (is == 1)
			return (s);
	}
	return (-1);
}
