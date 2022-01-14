/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/20 12:14:49 nneronin
 * Updated: 2021/05/08 15:03:23 nneronin
 */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	str = ft_strnew((len));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(s[i]);
		i++;
	}
	return (str);
}
