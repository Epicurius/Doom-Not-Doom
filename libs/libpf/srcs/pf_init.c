/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin
 */

#include "libpf.h"

void	pf_init(t_pf *p, FILE *fp, char *buffer, int size)
{
	ft_memset(p, 0, sizeof(t_pf));
	p->chars = 0;
	p->print_len = 0;
	p->fp = fp;
	p->buffer = buffer;
	p->size = size;
	reset_options(p);
}

