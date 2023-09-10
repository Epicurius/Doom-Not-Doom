/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Jony Salmi <jony.salmi@gmail.com>
 */

#include "libui.h"

char	**ft_strsplitwhitespace(char *str)
{
	char	**arr;
	int		i;
	int		prev_i;
	int		wc;

	if (!str)
		return (NULL);
	arr = malloc(sizeof(char *) * (actual_word_count(str) + 1));
	prev_i = 0;
	i = -1;
	wc = -1;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
		{
			arr[++wc] = ft_strsub(str, prev_i, i - prev_i);
			while (ft_isspace(str[++i]))
				;
			prev_i = i;
		}
	}
	if (i - prev_i > 0)
		arr[++wc] = ft_strsub(str, prev_i, i - prev_i);
	arr[++wc] = NULL;
	return (arr);
}

char	*create_final(char **arr)
{
	char	*final;
	char	*trim;
	int		i;

	final = NULL;
	i = -1;
	while (arr[++i])
	{
		trim = ft_strtrim(arr[i]);
		if (!trim)
			continue ;
		ft_stradd(&final, trim);
		if (arr[i + 1])
			ft_straddchar(&final, ' ');
		ft_strdel(&trim);
	}
	ft_arraydel(arr);
	return (final);
}

/*
 * Remove all whitespace at the ends,
 * replace all whitespace with space,
 * remove comments.
*/
char	*ft_supertrim(char *str)
{
	char	*trim;
	char	**arr;

	if (!str)
		return (NULL);
	trim = ft_strtrim(str);
	if (!trim)
		return (NULL);
	if (trim[0] && trim[0] == '/' && trim[1] && trim[1] == '/')
	{
		ft_strdel(&trim);
		return (NULL);
	}
	arr = ft_strsplitwhitespace(trim);
	ft_strdel(&trim);
	return (create_final(arr));
}

char	**ft_strsplitfirstoccurence(char *str, char c)
{
	char	**arr;
	int		i;

	if (!str)
		return (NULL);
	arr = ft_memalloc(sizeof(char *) * 3);
	i = -1;
	while (str[++i] && str[i] != c)
		;
	arr[0] = ft_strsub(str, 0, i);
	if (str[i] == c && str[i + 1])
		arr[1] = ft_strsub(str, i + 1, ft_strlen(str) - 1);
	return (arr);
}

/*
 * splits at first occurence of either delim 'b' or delim 'c';
*/
char	**ft_strsplitfirstoccurenceor(char *str, char b, char c)
{
	char	**arr;
	int		i;

	if (!str)
		return (NULL);
	arr = ft_memalloc(sizeof(char *) * 3);
	i = -1;
	while (str[++i] && str[i] != c && str[i] != b)
		;
	arr[0] = ft_strsub(str, 0, i);
	if (str[i] == c || str[i] == b)
		arr[1] = ft_strsub(str, i + 1, ft_strlen(str) - 1);
	return (arr);
}
