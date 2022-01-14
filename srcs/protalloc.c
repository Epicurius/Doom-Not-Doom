/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/05/17 18:18:01 nneronin
 * Updated: 2022/01/07 16:28:44 nneronin
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
	if (mem)
	{
		ft_memset(mem, FALSE, size);
		return (mem);
	}
	LG_ERROR("protalloc fail.");
	return (NULL);
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
