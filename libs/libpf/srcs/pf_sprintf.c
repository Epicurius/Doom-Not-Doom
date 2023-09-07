/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin
 */

#include "libpf.h"

int	ft_sprintf(char *str, const char *restrict format, ...)
{
	t_pf	p;

	if (!format)
		return (-1);
	pf_init(&p, NULL, str, PF_BUFF_SIZE);
	va_start(p.ap, format);
	pf_read_format((char *)format, &p);
	va_end(p.ap);
	str[p.chars] = '\0';
	return (p.print_len);
}

int	ft_snprintf(char *str, int len, const char *restrict format, ...)
{
	t_pf	p;

	if (!format)
		return (-1);
	pf_init(&p, NULL, str, len);
	va_start(p.ap, format);
	pf_read_format((char *)format, &p);
	va_end(p.ap);
	str[len] = '\0';
	if ((int)p.chars < len)
		str[p.chars] = '\0';
	return (p.print_len);
}

