/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:17:33 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/13 08:56:03 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

static char	is_valid_specifier(t_pf *p)
{
	if (!(ft_strchr("diouxXcsfp", *p->format)))
	{
		p->invalid = p->format;
		if (*p->format == '\0')
			p->format--;
		return (0);
	}
	if (*p->format == 'X')
		p->caps = 1;
	return (*p->format);
}

static void	read_format2(t_pf *p)
{
	if (ft_strchr("-+# 0", *p->format))
		read_flags(p);
	if (*p->format >= '1' && *p->format <= '9')
		read_width(p);
	if (*p->format == '.')
		read_precision(p);
	if (*p->format == '*')
		read_wildcard(p);
	if (ft_strchr("lhzjL", *p->format))
		read_size(p);
}

void	pf_read_format(const char *format, t_pf *p)
{
	p->format = (char *)format;
	while (*p->format)
	{
		if (*p->format == '%' && (*p->format + 1))
		{
			p->format++;
			while (ft_strchr("#+-0* .123456789lhzjL", *p->format))
				read_format2(p);
			specifier_sorter(p, is_valid_specifier(p));
		}
		else if (*p->format == '{')
			pf_specials(p);
		else
			fill_buffer(p, p->format, 1);
		reset_options(p);
		p->format++;
	}
}
