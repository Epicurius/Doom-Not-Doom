/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/20 10:31:45 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (0);
	str[size] = '\0';
	while (size--)
		str[size] = '\0';
	return (str);
}
