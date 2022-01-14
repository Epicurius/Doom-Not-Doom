/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/24 17:50:56 nneronin
 * Updated: 2021/05/08 14:28:44 nneronin
 */

#include "libft.h"

int	ft_wordcount(const char *s, char c)
{
	int	wc;
	int	i;

	i = 0;
	wc = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			wc++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (wc);
}
