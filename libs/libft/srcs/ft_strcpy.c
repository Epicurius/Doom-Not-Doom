/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 12:47:14 nneronin
 * Updated: 2021/05/08 14:32:58 nneronin
 */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	x;

	x = 0;
	while (src[x] != '\0')
	{
		dest[x] = src[x];
		++x;
	}
	dest[x] = '\0';
	return (dest);
}
