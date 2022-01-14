/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/14 10:50:50 nneronin
 * Updated: 2021/05/14 10:53:22 nneronin
 */

#include "libft.h"

void	*ft_memdup(const void *mem, size_t size)
{
	void	*out;

	out = ft_memalloc(size);
	if (out != NULL)
		ft_memcpy(out, mem, size);
	return (out);
}
