/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "doom.h"

/*
 *	A malloc that sets all bytes to NULL
 *	If memory allocation fails, will display error message
 *	[ERROR]	Malloc: file, function, line number;
 *	and exit(1), so not to segfault the program later on;
 */
void	*protalloc(size_t size)
{
	void	*mem;

	mem = malloc(sizeof(*mem) * size);
	if (!mem)
		LG_ERROR("failed to allocate memory.");

	ft_memset(mem, 0, size);
	return (mem);
}

/*
 *	Resets the sectbool list with FALSE(0) and sets current sector to TRUE(1).
 */
void	reset_sectbool(t_doom *doom, int curr_sect)
{
	ft_memset(doom->sectbool, FALSE, doom->nb.sectors);
	if (curr_sect >= 0)
		doom->sectbool[curr_sect] = TRUE;
}
