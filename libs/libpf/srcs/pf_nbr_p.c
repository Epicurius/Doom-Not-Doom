/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 15:06:27 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/12 15:18:34 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

static unsigned long	type_cast(t_pf *p)
{
	void	*pointer;

	pointer = va_arg(p->ap, void *);
	return ((unsigned long)pointer);
}

void	pf_nbr_p(t_pf *p)
{
	unsigned long	nb;

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
