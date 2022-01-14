/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 11:58:56 nneronin
 * Updated: 2021/12/11 16:04:16 jsalmi
 */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		x;

	x = -1;
	if (!src)
		return (NULL);
	while (src[++x] != '\0')
		;
	dest = malloc(sizeof(char) * (x + 1));
	if (!dest)
		return (NULL);
	x = -1;
	while (src[++x])
		dest[x] = src[x];
	dest[x] = '\0';
	return (dest);
}
