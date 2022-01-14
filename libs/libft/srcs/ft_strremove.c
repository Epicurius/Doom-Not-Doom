/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2019/10/16 15:50:42 jsalmi
 * Updated: 2021/07/03 08:49:51 jsalmi
 */

#include "libft.h"

char	*ft_strremove(char *str, const char *sub)
{
	char	*p;
	char	*q;
	char	*r;
	size_t	len;

	r = ft_strstr(str, sub);
	q = r;
	if (r != NULL)
	{
		len = ft_strlen(sub);
		p = r + len;
		r = ft_strstr(p, sub);
		while (r != NULL)
		{
			p = r + len;
			r = ft_strstr(p, sub);
			while (p < r)
				*q++ = *p++;
		}
		*q++ = *p++;
		while (*q != '\0')
			*q++ = *p++;
	}
	return (str);
}
