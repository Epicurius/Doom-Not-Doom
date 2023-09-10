/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

void	put_left_spaces(t_pf *p)
{
	while (p->padding.left_spaces > 0)
	{
		fill_buffer(p, " ", 1);
		p->padding.left_spaces--;
	}
}

void	put_sign(t_pf *p, long nb)
{
	if (p->padding.sign)
	{
		if (nb < 0)
			fill_buffer(p, "-", 1);
		else if (p->flag.plus)
			fill_buffer(p, "+", 1);
		else if (p->flag.space)
			fill_buffer(p, " ", 1);
	}
}

void	put_zeros(t_pf *p)
{
	while (p->padding.zeros > 0)
	{
		fill_buffer(p, "0", 1);
		p->padding.zeros--;
	}
}

void	put_right_spaces(t_pf *p)
{
	while (p->padding.right_spaces > 0)
	{
		fill_buffer(p, " ", 1);
		p->padding.right_spaces--;
	}
}
