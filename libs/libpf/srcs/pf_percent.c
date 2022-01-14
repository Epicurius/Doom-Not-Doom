/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:45:08 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 20:39:08 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

void	pf_putpercent(t_pf *p)
{
	if (!p->flag.minus && p->flag.zero)
		p->padding.zeros = p->min_width - 1;
	if (p->padding.zeros < 0)
		p->padding.zeros = 0;
	space_padding(p, 1);
	put_left_spaces(p);
	put_zeros(p);
	fill_buffer(p, "%", 1);
	put_right_spaces(p);
}
