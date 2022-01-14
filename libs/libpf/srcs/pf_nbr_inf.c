/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_nbr_inf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:52:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 20:42:00 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

static void	set_fpadding_infinite(t_pf *p, long double nb)
{
	p->padding.size = 3;
	if (p->flag.plus || p->flag.space || nb == -1.0 / 0.0)
	{
		p->padding.sign = 1;
		p->padding.size++;
	}
	if (!p->flag.minus)
		p->padding.left_spaces = p->min_width - p->padding.size;
	else
		p->padding.right_spaces = p->min_width - p->padding.size;
}

int	pf_nbr_inf(t_pf *p, long double nb)
{
	if (nb == 1.0 / 0.0 || nb == -1.0 / 0.0 || nb != nb)
	{
		set_fpadding_infinite(p, nb);
		put_left_spaces(p);
		if (nb == -1.0 / 0.0)
			fill_buffer(p, "-", 1);
		else if (p->flag.plus)
			fill_buffer(p, "+", 1);
		else if (p->flag.space)
			fill_buffer(p, " ", 1);
		put_zeros(p);
		if (nb == -1.0 / 0.0)
			fill_buffer(p, "inf", 3);
		else if (nb == 1.0 / 0.0)
			fill_buffer(p, "inf", 3);
		else
			fill_buffer(p, "nan", 3);
		put_right_spaces(p);
		return (1);
	}
	return (0);
}
