/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 11:43:57 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 19:14:46 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
