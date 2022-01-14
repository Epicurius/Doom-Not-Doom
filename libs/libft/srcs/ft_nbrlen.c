/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/24 16:57:15 nneronin
 * Updated: 2021/05/16 11:09:31 nneronin
 */

#include "libft.h"

int	ft_nbrlen(long nbr)
{
	int	len;

	len = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}
