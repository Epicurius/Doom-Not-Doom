/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/20 10:53:23 nneronin
 * Updated: 2021/05/08 14:32:27 nneronin
 */

#include "libft.h"

void	ft_strclr(char *s)
{
	size_t	x;

	x = 0;
	while (s[x] != '\0')
	{
		s[x] = '\0';
		x++;
	}
}
