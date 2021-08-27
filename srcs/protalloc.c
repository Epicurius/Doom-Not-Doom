/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:18:01 by nneronin          #+#    #+#             */
/*   Updated: 2021/08/27 15:58:37 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
 *	A malloc that sets all bytes to NULL
 *	If memory allocation fails, will display error message
 *	[ERROR]	Malloc: file, function, line number;
 *	and exit(1), so not to segfault the program later on;
 */
void	*protalloc(size_t size, char *file, const char *func, int line)
{
	void	*mem;

	mem = malloc(sizeof(*mem) * size);
	if (mem)
	{
		ft_bzero(mem, size);
		return (mem);
	}
	ft_printf("{RED}[ERROR]{RESET}\tMalloc: %s : %s : %d\n", file, func, line);
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
