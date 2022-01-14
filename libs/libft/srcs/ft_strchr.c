/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/18 11:39:37 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str && *str != c)
		str++;
	if (*str != (char)c)
		return (0);
	return ((char *)str);
}
