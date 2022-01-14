/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:51:19 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 20:36:50 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

static void	pf_putlong(long nb, t_pf *p)
{
	char	c;

	if (nb > 0)
		nb = -nb;
	if (nb > -10)
	{
		c = '0' - nb;
		fill_buffer(p, &c, 1);
	}
	else
	{
		pf_putlong(nb / 10, p);
		pf_putlong(nb % 10, p);
	}
}

static void	set_padding(t_pf *p, long nb)
{
	if (nb < 0 || p->flag.plus || p->flag.space)
		p->padding.sign = 1;
	if (nb == 0 && p->precision != 0)
		p->padding.size = 1;
	while (nb != 0)
	{
		p->padding.size++;
		nb /= 10;
	}
	if (p->precision != -1)
		p->padding.zeros = p->precision - p->padding.size;
	else if (!p->flag.minus && p->flag.zero)
		p->padding.zeros = p->min_width - p->padding.size
			- p->padding.sign;
	if (p->padding.zeros < 0)
		p->padding.zeros = 0;
	space_padding(p, p->padding.sign);
}

static long	type_cast(t_pf *p)
{
	long	nb;

	nb = va_arg(p->ap, long);
	if (p->size_bytes == 1)
		nb = (char)nb;
	else if (p->size_bytes == 2)
		nb = (int)nb;
	else if (p->size_bytes == 4)
		nb = (int)nb;
	return (nb);
}

void	pf_nbr(t_pf *p)
{
	long	nb;

	nb = type_cast(p);
	set_padding(p, nb);
	put_left_spaces(p);
	put_sign(p, nb);
	put_zeros(p);
	if (nb != 0 || p->precision != 0)
		pf_putlong(nb, p);
	put_right_spaces(p);
}
