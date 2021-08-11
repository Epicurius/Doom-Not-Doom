/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:18:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/11 10:38:14 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	A malloc that sets all bytes to NULL
 *	If memory allocation fails, will display error message
 *	(with custom string if given)
 *	and exit(1), so not to segfaault the program later on;
 */
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

/*
 *	Resets the sectbool list with FALSE(0) and sets current sector to TRUE(1).
 */
void	reset_sectbool(t_doom *doom, int curr_sect)
{
	ft_memset(doom->sectbool, FALSE, 4 * doom->nb.sectors);
	doom->sectbool[curr_sect] = TRUE;
}
