/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

void	reset_options(t_pf *p)
{
	p->flag.minus = 0;
	p->flag.plus = 0;
	p->flag.zero = 0;
	p->flag.space = 0;
	p->flag.hash = 0;
	p->min_width = 0;
	p->padding.size = 0;
	p->padding.sign = 0;
	p->padding.zeros = 0;
	p->padding.right_spaces = 0;
	p->padding.left_spaces = 0;
	p->precision = -1;
	p->size_bytes = 4;
	p->caps = 0;
	p->invalid = "\0";
}
