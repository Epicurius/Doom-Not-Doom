/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin
 */

#include "libpf.h"
#include <fcntl.h>

void	error_msg(const char *restrict format, ...)
{
	t_pf	p;
	char	buff[PF_BUFF_SIZE];

	write(1, "\x1b[31m[ERROR]\x1b[00m", 17);
	if (format)
	{
		write(1, "\t", 1);
		pf_init(&p, stderr, buff, PF_BUFF_SIZE);
		va_start(p.ap, format);
		pf_read_format((char *)format, &p);
		fwrite(p.buffer, p.chars, 1, p.fp);
		va_end(p.ap);
	}
	else
		write(1, "\n", 1);
	exit(1);
}
