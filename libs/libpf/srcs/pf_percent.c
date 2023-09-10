/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

void	pf_putpercent(t_pf *p)
{
	if (!p->flag.minus && p->flag.zero)
		p->padding.zeros = p->min_width - 1;
	if (p->padding.zeros < 0)
		p->padding.zeros = 0;
	space_padding(p, 1);
	put_left_spaces(p);
	put_zeros(p);
	fill_buffer(p, "%", 1);
	put_right_spaces(p);
}
