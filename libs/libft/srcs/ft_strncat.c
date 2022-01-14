/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 14:46:52 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (dest[x])
		x++;
	while (n-- && src[y])
	{
		dest[x] = src[y];
		x++;
		y++;
	}
	dest[x] = '\0';
	return (dest);
}
