/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/20 10:27:31 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_memdel(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}
