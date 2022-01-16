/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_help5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsalmi <jsalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:23:02 by jsalmi            #+#    #+#             */
/*   Updated: 2021/12/10 19:23:05 by jsalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libui.h"

/*
 * Returns text starting from char[0] till
 * 	the char at pos x (coordinate on the screen)
*/
char	*get_text_to_char_at_x(char *str, int x, TTF_Font *font)
{
	char	*result;
	int		char_w;
	int		total_w;
	int		i;
	char	temp[2];

	total_w = 0;
	i = -1;
	temp[1] = '\0';
	while (str[++i] && x < total_w)
	{
		temp[0] = str[i];
		TTF_SizeText(font, temp, &char_w, NULL);
		total_w += char_w;
	}
	result = ft_strsub(str, 0, i);
	return (result);
}

/*
 * Returns x of the "nth_char" position in the str.
 * NOTE: we assume that char[0] is at 0 x.
*/
int	get_x_of_char_in_text(char *str, int nth_char, TTF_Font *font)
{
	int		result;
	char	*temp;

	temp = ft_strndup(str, nth_char);
	TTF_SizeText(font, temp, &result, NULL);
	ft_strdel(&temp);
	return (result);
}

/*
 * Returns how many:eth char is at position x in the str.
 * NOTE: assuming str[0] is at x : 0 .
*/
int	get_nth_char_of_text_at_x(char *str, int x, TTF_Font *font)
{
	int		char_w;
	int		total_w;
	int		i;
	char	temp[2];

	total_w = 0;
	i = -1;
	temp[1] = '\0';
	while (str[++i] && total_w < x)
	{
		temp[0] = str[i];
		TTF_SizeText(font, temp, &char_w, NULL);
		total_w += char_w;
	}
	return (i);
}

/*
 * Every word should have whitespace between them;
*/
int	actual_word_count(char *str)
{
	int		count;
	int		i;

	if (!str)
		return (0);
	i = -1;
	count = 1;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
		{
			count++;
			while (ft_isspace(str[++i]))
				;
		}
	}
	return (count);
}
