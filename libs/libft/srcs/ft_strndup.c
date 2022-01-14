/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/09/24 14:49:30 nneronin
 * Updated: 2021/05/08 14:40:04 nneronin
 */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	size_t	counter;
	char	*sdest;

	counter = 0;
	sdest = (char *)ft_memalloc(sizeof(char) * (len + 1));
	if (!sdest)
		return (NULL);
	while (s1[counter] != '\0' && counter < len)
	{
		sdest[counter] = s1[counter];
		counter++;
	}
	sdest[counter] = '\0';
	return (sdest);
}
