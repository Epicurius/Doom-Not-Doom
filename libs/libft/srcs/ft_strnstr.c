/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/18 11:44:38 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *ne, size_t n)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	if (!ne[y])
		return ((char *)h);
	while (h[x] != '\0' && x < n)
	{
		y = 0;
		while (h[x + y] == ne[y] && h[x + y] != '\0' && x + y < n)
		{
			y++;
			if (ne[y] == '\0')
				return ((char *)&h[x]);
		}
		x++;
	}
	return (0);
}
