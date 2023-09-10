/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "launcher.h"

static int	find_root_length(char *root, char delim)
{
	int	i;

	i = 0;
	while (root[i])
		i++;
	while (i && root[i] != delim)
		i--;
	root[++i] = '\0';
	return (i);
}

#if __APPLE__

void	get_root(char *root, int *rlen)
{
	char		*path;
	uint32_t	len;

	len = PATH_MAX - 2;
	_NSGetExecutablePath(root, &len);
	path = realpath(root, NULL);
	*rlen = find_root_length(path, '/');
	ft_strcpy(root, path);
	free(path);
}

#else

void	get_root(char *root, int *rlen)
{
	char	buffer[PATH_MAX];

	GetModuleFileName(NULL, buffer, PATH_MAX);
	*rlen = find_root_length(buffer, '\\');
	ft_strcpy(root, buffer);
}

#endif