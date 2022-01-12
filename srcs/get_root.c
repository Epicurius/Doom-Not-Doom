/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:49:47 by nneronin          #+#    #+#             */
/*   Updated: 2022/01/12 17:59:06 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

#if __APPLE__

void	get_root(char *root, int *rlen)
{
	char		*path;
	uint32_t	len;

	len = PATH_MAX - 2;
	/* Get full path can have small errors */
	_NSGetExecutablePath(root, &len);
	/*	Remove "/./" */
	path = realpath(root, NULL);
	*rlen = ft_strlen(path) - 4;
	ft_strncpy(root, path, *rlen);
	free(path);
}

#else

void	get_root(char *root, int *rlen)
{
	LPSTR	buffer[PATH_MAX];

	GetModuleFileName(NULL, buffer, PATH_MAX);
	ft_strcpy(root, buffer);
	*rlen = ft_strlen(root);
}

#endif