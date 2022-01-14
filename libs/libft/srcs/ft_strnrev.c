/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/14 17:32:51 nneronin
 * Updated: 2021/05/14 17:33:44 nneronin
 */

#include "libft.h"

void	ft_strnrev(char *str, int len)
{
	int		i;
	int		len_tmp;
	char	tmp;

	i = 0;
	len_tmp = len;
	while (i < len)
	{
		tmp = str[i];
		str[i] = str[len - 1];
		str[len - 1] = tmp;
		i++;
		len--;
	}
	str[len_tmp] = '\0';
}
