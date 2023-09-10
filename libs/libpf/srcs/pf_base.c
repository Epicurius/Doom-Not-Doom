/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "libpf.h"

static void	recurse_base(t_pf *p, unsigned long nb, unsigned int l, char *base)
{
	if (nb < l)
		fill_buffer(p, &base[nb], 1);
	else
	{
		recurse_base(p, nb / l, l, base);
		recurse_base(p, nb % l, l, base);
	}
}

void	pf_base(t_pf *p, unsigned long nb, char *base)
{
	unsigned int	l;
	unsigned int	i;

	l = 0;
	i = 0;
	while (base[l])
	{
		if (base[l] <= ' ' || ft_strchr("~+-", base[l]))
			return ;
		i = l + 1;
		while (base[i])
		{
			if (base[l] == base[i])
				return ;
			i++;
		}
		l++;
	}
	if (l > 1)
		recurse_base(p, nb, l, base);
}
