/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 14:11:22 nneronin
 * Updated: 2021/07/26 14:34:30 nneronin
 */

#include "libft.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

float	ft_fmin(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_fmax(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}
