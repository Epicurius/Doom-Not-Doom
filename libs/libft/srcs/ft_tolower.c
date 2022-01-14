/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 17:28:41 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c <= 'Z' && c >= 'A')
		return (c + 32);
	return (c);
}
