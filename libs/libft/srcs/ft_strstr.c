/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 15:48:50 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!needle[y])
		return ((char *)&haystack[x]);
	while (haystack[x] != '\0')
	{
		y = 0;
		while (haystack[x + y] == needle[y] && haystack[x + y] != '\0')
		{
			if (needle[y + 1] == '\0')
				return ((char *)&haystack[x]);
			y++;
		}
		x++;
	}
	return (0);
}
