/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/20 11:00:11 nneronin
 * Updated: 2021/05/08 14:34:51 nneronin
 */

#include "libft.h"

void	ft_striter(char *s, void (*f)(char *))
{
	int	x;

	x = 0;
	while (s[x] != '\0')
	{
		f(&s[x]);
		x++;
	}
}
