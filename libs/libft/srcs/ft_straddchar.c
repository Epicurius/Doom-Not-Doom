/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/09/24 11:33:30 jsalmi
 * Updated: 2021/07/03 09:00:18 jsalmi
 */

#include "libft.h"

void	ft_straddchar(char **str, char c)
{
	char	*temp;

	temp = ft_strnew(1);
	temp[0] = c;
	if (*str == NULL)
		*str = ft_strdup(temp);
	else
		ft_stradd(str, temp);
	ft_strdel(&temp);
}
