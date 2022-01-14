/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/24 17:01:14 nneronin
 * Updated: 2021/05/08 14:06:12 nneronin
 */

#include "libft.h"

int	ft_iswspace(int c)
{
	if (c == '\t' || c == ' ' || c == '\n')
		return (1);
	return (0);
}
