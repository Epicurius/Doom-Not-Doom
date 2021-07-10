/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:18:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/10 13:49:44 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*ft_pmalloc(size_t size, char *str)
{
	void	*mem;

	mem = malloc(sizeof(*mem) * size);
	if (mem)
	{
		ft_bzero(mem, size);
		return (mem);
	}
	write(1, "\x1b[31m[ERROR]\x1b[00m\tMalloc", 24);
	if (!str)
		ft_printf("\t%s\n", str);
	else
		write(1, "\n", 1);
	exit(1);
}
