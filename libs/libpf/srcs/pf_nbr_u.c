/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:35:02 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 20:36:17 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

static void	pf_putulong(unsigned long nb, t_pf *p)
{
	char	c;

	if (nb < 10)
	{
		c = '0' + nb;
		fill_buffer(p, &c, 1);
	}
	else
	{
		pf_putulong(nb / 10, p);
		pf_putulong(nb % 10, p);
	}
}

static void	set_padding(t_pf *p, unsigned long nb)
{
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
		p->padding.zeros = p->min_width - p->padding.size;
	if (p->padding.zeros < 0)
		p->padding.zeros = 0;
	space_padding(p, 0);
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

void	pf_nbr_u(t_pf *p)
{
	unsigned long	nb;

	nb = type_cast(p);
	set_padding(p, nb);
	put_left_spaces(p);
	put_zeros(p);
	if (nb != 0 || p->precision != 0)
		pf_putulong(nb, p);
	put_right_spaces(p);
}
