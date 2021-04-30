/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmpv2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:37:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/04/30 14:28:13 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

t_bmp	*read_bmp(char *file)
{
	int		fd;
	t_bmp	*bmp;

	fd = open(file, O_RDONLY);
	bmp = malloc(sizeof(t_bmp));
	if (!bmp)
		return (NULL);
	if (read(fd, &bmp->header, sizeof(bmp->header)) <= 0)
		return (NULL);
	bmp->data = malloc(sizeof(*bmp->data) * bmp->header.image_size_bytes);
	if (!bmp->data)
		return (NULL);
	read(fd, bmp->data, bmp->header.image_size_bytes);
	close(fd);
	return (bmp);
}

void	create_path_and_name(char *file, char **path, char **name)
{
	int		i;
	char	*temp;

	i = ft_strlen(file);
	temp = ft_strndup(file, i - 4);
	while (file[i - 1] != '/' && i > 0)
		i--;
	(*name) = ft_strdup(&temp[i]);
	(*path) = ft_strdup(temp);
	free(temp);
}

void	free_bmp(t_bmp *bmp)
{
	free(bmp->data);
	free(bmp);
}

void	free_bxpm(t_bxpm *bxpm)
{
	free(bxpm->clr);
	free(bxpm->pix);
	free(bxpm);
}

int	main(int ac, char **av)
{
	int		i;
	t_bmp	*bmp;
	t_bxpm	*bxpm;
	char	*path;
	char	*name;

	i = 0;
	if (ac == 1)
		return (0);
	while (++i < ac)
	{
		if (!ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".bmp"))
			continue ;
		if (!(bmp = read_bmp(av[i])))
		{
			ft_printf("{RED}ERROR{RESET}\n");
			return (0);
		}
		ft_printf("Read\t%s\n", av[i]);
		if (!(bxpm = create_bxpm(bmp)))
		{
			ft_printf("{RED}ERROR{RESET}\n");
			return (0);
		}
		ft_printf("Create\t%s\n", av[i]);
		create_path_and_name(av[i], &path, &name);
		write_bxpm(bxpm, path, name);
		ft_printf("Writing\t%s.bxpm\n", path);
		write_bbmp(bxpm, path, name);
		ft_printf("Writing\t%s.bbmp\n", path);
		free_bmp(bmp);
		free_bxpm(bxpm);
		ft_printf("{GREEN}Done with: %s{RESET}\n", path);
		free(path);
		free(name);
	}
	return (0);
}
