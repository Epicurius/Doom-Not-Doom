/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_reset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:18:15 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/15 20:17:05 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

void	reset_options(t_pf *p)
{
	p->flag.minus = 0;
	p->flag.plus = 0;
	p->flag.zero = 0;
	p->flag.space = 0;
	p->flag.hash = 0;
	p->min_width = 0;
	p->padding.size = 0;
	p->padding.sign = 0;
	p->padding.zeros = 0;
	p->padding.right_spaces = 0;
	p->padding.left_spaces = 0;
	p->precision = -1;
	p->size_bytes = 4;
	p->caps = 0;
	p->invalid = "\0";
}
