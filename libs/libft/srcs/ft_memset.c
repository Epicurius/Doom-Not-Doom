/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/16 14:18:03 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*str;
	unsigned char	cchar;

	i = 0;
	str = b;
	cchar = c;
	while (i < len)
	{
		str[i] = cchar;
		i++;
	}
	return (b);
}
