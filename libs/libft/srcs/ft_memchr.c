/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 10:41:55 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*asd;

	asd = (char const *)str;
	while (n != 0)
	{
		if (*asd == (char)c)
			return ((void *)asd);
		asd++;
		n--;
	}
	return (0);
}
