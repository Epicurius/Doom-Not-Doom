/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/22 16:54:30 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
