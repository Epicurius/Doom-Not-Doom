/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/06 09:06:49 nneronin
 * Updated: 2021/12/10 09:21:03 jsalmi
 */

#include "libft.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_fswap(float *a, float *b)
{
	float	tmp;

	tmp = 0;
	tmp = *a;
	*a = *b;
	*b = tmp;
}
