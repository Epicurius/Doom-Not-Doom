/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/16 14:32:06 nneronin
 * Updated: 2021/05/14 10:54:05 nneronin
 */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		x;
	char		*str;
	const char	*source;

	str = dst;
	source = src;
	x = 0;
	if (!n || str == source)
		return (dst);
	while (x < n)
	{
		str[x] = source[x];
		x++;
	}
	return (dst);
}
