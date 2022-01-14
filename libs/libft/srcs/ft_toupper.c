/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 17:17:43 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c <= 'z' && c >= 'a')
		return (c - 32);
	return (c);
}
