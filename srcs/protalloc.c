/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:18:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/01 09:14:16 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	*protalloc(size_t size, char *str)
{
	void	*mem;

	mem = malloc(sizeof(*mem) * size);
	if (mem)
	{
		ft_bzero(mem, size);
		return (mem);
	}
	write(1, "\x1b[31m[ERROR]\x1b[00m\t(", 19);
	if (!str)
		ft_putstr(str);
	write(1, ") Out of memory\n", 16);
	exit(1);
}