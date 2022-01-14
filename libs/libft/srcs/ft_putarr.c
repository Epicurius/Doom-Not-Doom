/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/11 10:10:12 jsalmi
 * Updated: 2021/12/11 10:10:12 jsalmi
 */

#include "libft.h"

void	ft_putarr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
	{
		ft_putstr(arr[i]);
		ft_putchar('\n');
	}
}
