/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

void	ft_strtrimwholearr(char **arr)
{
	int		i;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		temp = ft_strtrim(arr[i]);
		ft_strdel(&arr[i]);
		arr[i] = temp;
	}
}

char	**ft_arrdup(char **src)
{
	char	**dest;
	int		ii;

	if (!src)
		return (NULL);
	ii = -1;
	while (src[++ii])
		;
	dest = malloc(sizeof(char *) * ii);
	ii = -1;
	while (src[++ii])
		dest[ii] = ft_strdup(src[ii]);
	dest[ii] = NULL;
	return (dest);
}

int	ft_strinarr(char *str, char **arr)
{
	int	ii;

	if (!str || !arr)
		return (0);
	ii = -1;
	while (arr[++ii])
		if (ft_strequ(str, arr[ii]))
			return (1);
	return (0);
}

int	ft_arrlen(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = -1;
	while (arr[++i])
		;
	return (i);
}

/*
 * returns arr;
*/
char	**ft_arradd(char **arr, char *add)
{
	int	len;

	if (!add)
		return (arr);
	len = ft_arrlen(arr);
	arr = realloc(arr, sizeof(char *) * (len + 2));
	arr[len] = ft_strdup(add);
	arr[len + 1] = NULL;
	return (arr);
}
