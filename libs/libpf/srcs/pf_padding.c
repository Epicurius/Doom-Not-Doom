/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

void	space_padding(t_pf *p, int extra)
{
	if (p->flag.minus)
		p->padding.right_spaces = p->min_width - p->padding.zeros
			- p->padding.size - extra;
	else
		p->padding.left_spaces = p->min_width - p->padding.zeros
			- p->padding.size - extra;
}

static void	float_padding_width(t_pf *p)
{
	if (!p->flag.minus)
	{
		if (p->flag.zero)
			p->padding.zeros = p->min_width - p->padding.size;
		else
			p->padding.left_spaces = p->min_width - p->padding.size;
	}
	else
		p->padding.right_spaces = p->min_width - p->padding.size;
}

void	set_float_padding(t_pf *p, long i_part, long double nb)
{
	p->padding.size = p->precision;
	if (p->precision > 0)
		p->padding.size += 1;
	if (i_part == 0)
		p->padding.size++;
	if (p->flag.hash)
		p->padding.size++;
	if (p->flag.plus || p->flag.space || nb < 0 || 1.0 / nb < 0)
	{
		p->padding.sign = 1;
		p->padding.size++;
	}
	while (i_part != 0)
	{
		p->padding.size++;
		i_part /= 10;
	}
	if (p->min_width > p->padding.size)
		float_padding_width(p);
}
