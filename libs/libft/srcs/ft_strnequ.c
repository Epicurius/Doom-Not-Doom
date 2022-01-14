/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/21 14:33:01 nneronin
 * Updated: 2021/05/08 14:41:30 nneronin
 */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (ft_strncmp(s1, s2, n))
		return (0);
	return (1);
}
