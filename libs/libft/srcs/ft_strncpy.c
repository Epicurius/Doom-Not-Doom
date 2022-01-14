/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 12:59:03 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n && src[x] != '\0')
	{
		dest[x] = src[x];
		++x;
	}
	while (x < n)
	{
		dest[x] = '\0';
		++x;
	}
	return (dest);
}
