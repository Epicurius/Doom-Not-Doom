/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/22 13:26:59 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}
