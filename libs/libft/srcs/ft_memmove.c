/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 10:31:25 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*tmp;
	const char	*src2;

	tmp = dst;
	src2 = src;
	if (dst > src)
	{
		while (n > 0)
		{
			n--;
			tmp[n] = src2[n];
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
