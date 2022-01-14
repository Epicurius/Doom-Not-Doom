/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/16 14:26:46 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	if (n > 0)
		ft_memset(str, 0, n);
}
