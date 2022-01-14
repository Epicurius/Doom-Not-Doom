/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/09/20 13:16:07 jsalmi
 * Updated: 2021/07/03 09:00:31 jsalmi
 */

#include "libft.h"

int	ft_stradd(char **dest, char *src)
{
	char	*temp;

	if (!src)
		return (0);
	if (!(*dest) || *dest == NULL)
	{
		*dest = ft_strdup(src);
		return (1);
	}
	temp = ft_strdup(*dest);
	ft_strdel(dest);
	*dest = ft_strjoin(temp, src);
	ft_strdel(&temp);
	return (1);
}
