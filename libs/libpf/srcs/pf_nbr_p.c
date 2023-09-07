/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

static unsigned long long	type_cast(t_pf *p)
{
	void	*pointer;

	pointer = va_arg(p->ap, void *);
	return (((unsigned long long)pointer));
}

void	pf_nbr_p(t_pf *p)
{
	unsigned long long	nb;

	nb = type_cast(p);
	if (p->flag.hash && (nb && (p->min_width != 0 && p->precision == -1)))
		p->padding.size += 2;
	set_zeros_base(p, nb, 16);
	if (p->flag.hash && (nb && !(p->min_width != 0 && p->precision == -1)))
		p->padding.size += 2;
	space_padding(p, 0);
	put_left_spaces(p);
	fill_buffer(p, "0x", 2);
	put_zeros(p);
	if ((nb || p->precision != 0) && p->caps)
		pf_base(p, nb, "0123456789ABCDEF");
	else if (nb || p->precision != 0)
		pf_base(p, nb, "0123456789abcdef");
	put_right_spaces(p);
}
