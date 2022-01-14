/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/18 09:49:46 nneronin
 * Updated: 2021/07/16 13:22:23 nneronin
 */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*mem;

	mem = malloc(size);
	if (!mem)
	{
		write(1, "\x1b[31m!![FT_MEMALLOC ERROR]!!\x1b[00m\n", 35);
		exit(1);
	}
	ft_memset(mem, 0, size);
	return (mem);
}
