/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 12:38:23 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/02 10:57:52 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
