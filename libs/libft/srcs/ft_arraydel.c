/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/11 10:09:29 jsalmi
 * Updated: 2021/12/11 10:09:30 jsalmi
 */

#include "libft.h"

void	ft_arraydel(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = -1;
	while (arr[++i])
		ft_strdel(&arr[i]);
	free(arr);
	arr = NULL;
}
