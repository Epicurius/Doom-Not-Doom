/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/14 17:26:05 nneronin
 * Updated: 2021/05/14 17:28:51 nneronin
 */

#include "libft.h"

void	ft_strrev(char *str)
{
	int		len;
	int		i;
	int		len_tmp;
	char	tmp;

	len = ft_strlen(str);
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
