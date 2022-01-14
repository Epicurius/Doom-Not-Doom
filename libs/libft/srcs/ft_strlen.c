/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/17 11:47:30 nneronin
 * Updated: 2021/05/08 14:37:25 nneronin
 */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*(str++))
		len++;
	return (len);
}
