/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filetostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 15:06:26 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/23 15:22:41 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

char	*ft_fdtostr(int fd, int i)
{
	char			*buf;
	char			*ret;
	unsigned int	bytes_read;

	buf = malloc(FTS_BUFF_SIZE);
	if (!buf)
		return (0);
	bytes_read = read(fd, buf, FTS_BUFF_SIZE);
	if (bytes_read == FTS_BUFF_SIZE)
		ret = ft_fdtostr(fd, i + FTS_BUFF_SIZE);
	else
	{
		ret = (char *)malloc(i + bytes_read + 1);
		ret[i + bytes_read] = '\0';
	}
	if (!ret)
		return (0);
	if (ret && bytes_read)
		ft_memcpy(ret + i, buf, bytes_read);
	else
		ret[i] = 0;
	free(buf);
	return (ret);
}

char	*ft_filetostr(char *file)
{
	int		fd;
	char	*str;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	str = ft_fdtostr(fd, 0);
	close(fd);
	return (str);
}
