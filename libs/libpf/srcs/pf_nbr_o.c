/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:55:18 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 20:49:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

void	set_zeros_base(t_pf *p, unsigned long nb, int base_len)
{
	if (nb == 0 && p->precision != 0)
		p->padding.size = 1;
	while (nb != 0)
	{
		p->padding.size++;
		nb /= base_len;
	}
	p->padding.zeros = 0;
	if (p->precision != -1)
		p->padding.zeros = p->precision - p->padding.size;
	else if ((!p->flag.minus && p->flag.zero))
		p->padding.zeros = p->min_width - p->padding.size;
	if (p->padding.zeros < 0)
		p->padding.zeros = 0;
}

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

void	pf_nbr_o(t_pf *p)
{
	unsigned long	nb;

	nb = type_cast(p);
	set_zeros_base(p, nb, 8);
	if (p->flag.hash && ((!p->padding.zeros && nb) || (!p->precision && !nb)))
		p->padding.size += 1;
	space_padding(p, 0);
	put_left_spaces(p);
	if (p->flag.hash && ((!p->padding.zeros && nb) || (!p->precision && !nb)))
		fill_buffer(p, "0", 1);
	put_zeros(p);
	if (p->precision || nb)
		pf_base(p, nb, "01234567");
	put_right_spaces(p);
}
