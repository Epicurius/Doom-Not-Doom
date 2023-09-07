/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

static const t_pf_style	g_pf_styles[11] =
{
	{"{RESET}", "\x1b[00m", 7},
	{"{RED}", "\x1b[31m", 5},
	{"{GREEN}", "\x1b[32m", 7},
	{"{YELLOW}", "\x1b[33m", 8},
	{"{BLUE}", "\x1b[34m", 6},
	{"{MAGENTA}", "\x1b[35m", 9},
	{"{CYAN}", "\x1b[36m", 6},
	{"{BOLD}", "\x1b[01m", 6},
	{"{ITALIC}", "\x1b[03m", 8},
	{"{UND}", "\x1b[04m", 5},
	{"{INVERT}", "\x1b[07m", 8}
};

static void	color_code(t_pf *p)
{
	int	len;
	int	code;

	len = 0;
	code = ft_atoi(p->format + 5);
	if (code >= 0 && code <= 9)
		len = 1;
	else if (code >= 10 && code <= 99)
		len = 2;
	else if (code >= 100 && code <= 255)
		len = 3;
	if (len == 0 || ft_strncmp((p->format + 5 + len), "}", 1))
	{
		fill_buffer(p, p->format, 1);
		return ;
	}
	if (fileno(p->fp) < 3)
	{
		fill_buffer(p, "\x1b[38;5;", 7);
		fill_buffer(p, p->format + 5, len);
		fill_buffer(p, "m", 1);
	}
	p->format += 5 + len;
}

static void	color_preset(t_pf *p)
{
	for (int i = 0; i < 11; i++)
	{
		if (!ft_strncmp(g_pf_styles[i].str, p->format, g_pf_styles[i].len))
		{
			if (fileno(p->fp) < 3)
				fill_buffer(p, g_pf_styles[i].code, 5);
			p->format += g_pf_styles[i].len - 1;
			return ;
		}
	}
	fill_buffer(p, p->format, 1);
}

void	pf_specials(t_pf *p)
{
	if (*p->format == '{' && ft_isupper(*(p->format + 1)))
	{
		if (!ft_strncmp(p->format, "{CLR:", 5))
			color_code(p);
		else
			color_preset(p);
	}
	else
	{
		fill_buffer(p, p->format, 1);
	}
}
