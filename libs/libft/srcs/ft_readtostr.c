/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readtostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 18:09:35 by nneronin          #+#    #+#             */
/*   Updated: 2021/06/20 18:11:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_rfts(int fd, int i)
{
	char		*buf;
	char		*ret;
	ssize_t		bytes_read;

	buf = malloc(GNL_BUFF_SIZE);
	if (!buf)
		return (0);
	bytes_read = read(fd, buf, GNL_BUFF_SIZE);
	if (bytes_read > 0)
		ret = ft_rfts(fd, i + GNL_BUFF_SIZE);
	else
		ret = (char *)malloc(i + 1);
	if (bytes_read < 0 || !ret)
		return (0);
	if (ret && bytes_read)
		ft_memcpy(ret + i, buf, bytes_read);
	else
		ret[i] = 0;
	free(buf);
	return (ret);
}

char	*ft_readtostr(int fd)
{
	if (fd < 0)
		return (0);
	return (ft_rfts(fd, 0));
}
