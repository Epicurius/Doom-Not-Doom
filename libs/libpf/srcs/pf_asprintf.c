/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin
 */

#include "libpf.h"

int	ft_asprintf(char **restrict ptr, const char *restrict format, ...)
{
	t_pf	p;
	char	buff[PF_BUFF_SIZE];

	if (!format)
		return (-1);
	pf_init(&p, stdout, buff, PF_BUFF_SIZE);
	va_start(p.ap, format);
	pf_read_format((char *)format, &p);
	va_end(p.ap);
	*ptr = ft_strndup(p.buffer, p.chars);
	return (p.print_len);
}
