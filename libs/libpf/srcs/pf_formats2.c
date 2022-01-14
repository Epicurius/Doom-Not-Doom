/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_formats2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 18:47:14 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/12 15:05:41 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpf.h"

void	specifier_sorter(t_pf *p, int c)
{
	if (c == 's')
		pf_str(p);
	else if (c == 'd')
		pf_nbr(p);
	else if (c == 'x')
		pf_nbr_x(p);
	else if (c == 'f')
		pf_float(p);
	else if (c == 'c')
		pf_char(p);
	else if (c == 'i')
		pf_nbr(p);
	else if (c == 'o')
		pf_nbr_o(p);
	else if (c == 'u')
		pf_nbr_u(p);
	else if (c == 'X')
		pf_nbr_x(p);
	else if (c == 'p')
		pf_nbr_p(p);
	else
		pf_invalid(p);
}

static inline void	flag_size(t_pf *p, int *l, int *h, int *lu)
{
	if (*p->format == 'l')
		*l += 1;
	if (*p->format == 'h')
		*h += 1;
	if (*p->format == 'L')
		*lu += 1;
	p->format++;
}

void	read_size(t_pf *p)
{
	int	l;
	int	h;
	int	lu;

	l = 0;
	h = 0;
	lu = 0;
	while (ft_strchr("lhzjL", *p->format))
		flag_size(p, &l, &h, &lu);
	if (l == 0 && h == 0)
		p->size_bytes = 4;
	else if (l >= 1)
		p->size_bytes = 8;
	else if (h == 1)
		p->size_bytes = 2;
	else if (h == 2)
		p->size_bytes = 1;
	if (lu >= 1)
		p->size_bytes = 16;
}

void	pf_invalid(t_pf *p)
{
	if (p->precision > 0)
		p->padding.zeros = p->precision - 1;
	else if (!p->flag.minus && p->flag.zero)
		p->padding.zeros = p->min_width - 1;
	if (p->padding.zeros < 0)
		p->padding.zeros = 0;
	space_padding(p, 1);
	put_left_spaces(p);
	put_zeros(p);
	if (*p->invalid != '\0')
		fill_buffer(p, p->invalid, 1);
	put_right_spaces(p);
}
