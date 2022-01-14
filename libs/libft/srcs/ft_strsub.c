/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/21 14:36:26 nneronin
 * Updated: 2021/12/08 15:53:53 nneronin
 */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || len == 0)
		return (NULL);
	str = malloc(len + 1);
	if (!len)
		return (0);
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
