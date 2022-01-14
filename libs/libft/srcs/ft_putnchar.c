/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/01/24 10:59:28 nneronin
 * Updated: 2021/05/08 14:17:49 nneronin
 */

#include "libft.h"

void	ft_putnchar(char c, int nbr)
{
	while (nbr > 0)
	{
		write(1, &c, 1);
		nbr--;
	}
}
