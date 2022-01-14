/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/12/15 13:05:43 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_putnstr(char *str, int n)
{
	int	x;

	x = 0;
	if (*str == '\0')
		return ;
	if (n < 0)
		ft_putstr(str);
	else
	{
		while (x != n)
		{
			if (str[x] == '\0')
				return ;
			write(1, &str[x], 1);
			x++;
		}
	}
}
