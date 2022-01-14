/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:42:12 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 21:01:29 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

static unsigned long	type_cast(t_pf *p)
{
	unsigned long	nb;

	nb = va_arg(p->ap, unsigned long);
	if (p->size_bytes == 1)
		nb = (unsigned char)nb;
	else if (p->size_bytes == 2)
		nb = (unsigned int)nb;
	else if (p->size_bytes == 4)
		nb = (unsigned int)nb;
	return (nb);
}

void	pf_nbr_x(t_pf *p)
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
	if ((p->flag.hash && nb) && p->caps)
		fill_buffer(p, "0X", 2);
	else if (p->flag.hash && nb)
		fill_buffer(p, "0x", 2);
	put_zeros(p);
	if ((nb || p->precision != 0) && p->caps)
		pf_base(p, nb, "0123456789ABCDEF");
	else if (nb || p->precision != 0)
		pf_base(p, nb, "0123456789abcdef");
	put_right_spaces(p);
}
