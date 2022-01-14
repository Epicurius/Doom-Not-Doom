/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/20 10:47:30 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_strdel(char **as)
{
	if (as)
	{
		free(*as);
		*as = NULL;
	}
}
