/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/22 16:56:22 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
