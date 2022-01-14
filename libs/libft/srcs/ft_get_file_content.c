/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:39:53 by nneronin          #+#    #+#             */
/*   Updated: 2021/12/08 15:40:24 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_get_file_content(char *file)
{
	char	*final;
	FILE	*fd;
	int		read_this_loop;
	int		read_total;
	int		i;

	fd = fopen(file, "r");
	final = NULL;
	read_this_loop = 0;
	read_total = 0;
	i = 1;
	while (fd)
	{
		final = realloc(final, sizeof(char) * (i * 100));
		read_this_loop = fread(final + read_total, 1, 100, fd);
		read_total += read_this_loop;
		i++;
		if (read_this_loop < 100)
			break ;
	}
	fclose(fd);
	return (final);
}
