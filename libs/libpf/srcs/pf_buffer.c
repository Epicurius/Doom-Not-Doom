/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

void	fill_buffer(t_pf *p, const char *s, unsigned int size)
{
	unsigned int	i;

	i = 0;
	if (p->print_len != -1)
		p->print_len += size;
	if (p->chars + size > MAX_INT)
		p->print_len = -1;
	if (p->chars + size >= p->size)
	{
		fwrite(p->buffer, p->chars, 1, p->fp);
		p->chars = 0;
	}
	if (size < p->size)
	{
		while (i < size)
		{
			p->buffer[p->chars] = s[i];
			i++;
			p->chars++;
		}
	}
	else
		fwrite(s, size, 1, p->fp);
}
