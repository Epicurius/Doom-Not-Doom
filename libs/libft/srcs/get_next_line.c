/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 12:20:31 by nneronin          #+#    #+#             */
/*   Updated: 2021/05/17 16:35:28 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	contains_zero(char *buf, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (buf[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	string_edit(char **file, const int fd, char **line, int char_nbr)
{
	int		i;

	if (char_nbr == 0 && file[fd][0] == '\0')
	{
		ft_strdel(&file[fd]);
		return (0);
	}
	i = ft_strchrlen(file[fd], '\n');
	if (i || file[fd][0] == '\n')
	{
		*line = ft_strsub(file[fd], 0, i);
		file[fd] = ft_strcut(file[fd], i + 1, 0);
		return (1);
	}
	i = ft_strchrlen(file[fd], '\0');
	if (i)
	{
		*line = ft_strdup(file[fd]);
		file[fd][0] = '\0';
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char		*file[GNL_FILE_NB];
	char			read_buffer[GNL_BUFF_SIZE + 1];
	int				char_nbr;

	if (fd < 0 || !line || GNL_BUFF_SIZE < 1 || read(fd, read_buffer, 0) < 0)
		return (-1);
	if (file[fd] == 0)
		file[fd] = ft_strnew(0);
	while (!ft_strchr(file[fd], '\n'))
	{
		char_nbr = read(fd, read_buffer, GNL_BUFF_SIZE);
		if (char_nbr < 0)
			return (-1);
		if (!char_nbr || contains_zero(read_buffer, char_nbr))
			break ;
		read_buffer[char_nbr] = '\0';
		file[fd] = ft_strjoinf(file[fd], read_buffer);
	}
	return (string_edit(file, fd, line, char_nbr));
}
