/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:18:53 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/08 14:27:23 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(int nbr)
{
	int	size;

	size = 0;
	if (nbr <= 0)
		size++;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

static char	*ft_fillstr(int size, int i, int nbr, char *str)
{
	while (size > i)
	{
		str[size - 1] = nbr % 10 + '0';
		nbr = nbr / 10;
		size--;
	}
	return (str);
}

char	*ft_itoa(int nbr)
{
	int		i;
	int		size;
	char	*str;

	i = 0;
	size = 0;
	size = ft_get_size(nbr);
	str = ft_strnew(size);
	if (!str)
		return (0);
	if (nbr == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		nbr = 147483648;
		i = 2;
	}
	if (nbr < 0)
	{
		str[0] = '-';
		i = 1;
		nbr = -nbr;
	}
	str = ft_fillstr(size, i, nbr, str);
	return (str);
}
