/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_input_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:16 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/17 12:27:11 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

void	remove_str_from_n_to_m(char **dest, int n, int m)
{
	char	*temp0;
	char	*temp1;
	int		len;

	if (!*dest || n == m || n < 0)
		return ;
	len = ft_strlen(*dest);
	if (len <= 0)
		return ;
	temp0 = ft_strsub(*dest, 0, n);
	temp1 = ft_strsub(*dest, m, len);
	ft_strdel(dest);
	*dest = ft_strjoin(temp0, temp1);
	ft_strdel(&temp0);
	ft_strdel(&temp1);
}

void	remove_char_after_nth_char(char **dest, int n)
{
	char	*temp0;
	char	*temp1;
	int		len;

	len = ft_strlen(*dest);
	temp0 = ft_strsub(*dest, 0, n - 1);
	temp1 = ft_strsub(*dest, n, len);
	ft_strdel(dest);
	*dest = ft_strjoin(temp0, temp1);
	ft_strdel(&temp0);
	ft_strdel(&temp1);
}

void	insert_str_after_nth_char(char **dest, char *src, int n)
{
	char	*temp0;
	char	*temp1;
	int		len;

	len = ft_strlen(*dest);
	temp0 = ft_strsub(*dest, 0, n);
	temp1 = ft_strsub(*dest, n, len);
	ft_stradd(&temp0, src);
	ft_stradd(&temp0, temp1);
	ft_strdel(dest);
	*dest = ft_strdup(temp0);
	ft_strdel(&temp0);
	ft_strdel(&temp1);
}

char	*str_remove_all_numbers(char *str)
{
	char	*final;
	char	temp[256];
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			temp[++j] = str[i];
	temp[++j] = '\0';
	final = ft_strdup(temp);
	return (final);
}

char	*str_remove_all_letters(char *str)
{
	char	*final;
	char	temp[256];
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i])
		if (!ft_isalpha(str[i]))
			temp[++j] = str[i];
	temp[++j] = '\0';
	final = ft_strdup(temp);
	return (final);
}
