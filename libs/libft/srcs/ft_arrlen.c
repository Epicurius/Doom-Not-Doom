/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/08 15:39:23 nneronin
 * Updated: 2021/12/08 15:39:24 nneronin
 */

#include "libft.h"

int	ft_arrlen(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}
