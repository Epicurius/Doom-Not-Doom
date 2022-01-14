/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2021/07/23 15:30:30 nneronin
 * Updated: 2021/07/23 15:33:57 nneronin
 */

#include <stdio.h>
#include "libft.h"

int	ft_compile_string(char *name, char *code)
{
	FILE	*proc;
	char	*gcc;

	gcc = ft_strjoin("gcc-o", name);
	gcc = ft_strjoinf(gcc, "-xc-");
	proc = popen(gcc, "w");
	free(gcc);
	if (!proc)
		return (0);
	fwrite(code, sizeof(char), strlen(code), proc);
	if (ferror(proc))
		return (0);
	if (pclose(proc) == -1)
		return (0);
	return (1);
}
