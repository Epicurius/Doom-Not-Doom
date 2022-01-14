/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 16:26:46 nneronin
 * Updated: 2021/05/08 14:20:16 nneronin
 */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	neg;

	res = 0;
	i = 0;
	neg = 1;
	if (!str[i])
		return (0);
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] > 47 && str[i] < 58)
	{
		res = 10 * res + (str[i] - 48);
		i++;
	}
	return (neg * res);
}
