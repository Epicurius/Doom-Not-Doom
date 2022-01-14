/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/08 14:30:08 nneronin
 * Updated: 2021/05/08 14:30:49 nneronin
 */

#include "libft.h"

int	ft_strarr_func(char **arr, void (*f)(char **))
{
	int	i;

	i = -1;
	while (arr[++i] != NULL)
		if (f != NULL)
			f(&arr[i]);
	return (i);
}
