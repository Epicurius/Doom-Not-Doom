/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 17:04:42 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
