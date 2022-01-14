/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 16:38:26 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c <= 'z' && c >= 'a'))
		return (c);
	else
		return (0);
}
