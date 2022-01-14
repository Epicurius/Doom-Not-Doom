/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/22 16:47:04 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
