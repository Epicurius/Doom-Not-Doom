/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/12/11 10:10:21 jsalmi
 * Updated: 2021/12/11 10:10:21 jsalmi
 */

#include "libft.h"

void	ft_strnclr(char *str, size_t n)
{
	if (!str)
		return ;
	while (--n)
		str[n] = '\0';
}
