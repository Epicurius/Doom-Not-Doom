/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 13:37:21 by nneronin          #+#    #+#             */
/*   Updated: 2021/09/04 12:05:58 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/libft.h"
#include "../../libs/libpf/libpf.h"
#include "../../libs/libbxpm/bxpm.h"

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

void	free_converter(t_bmp *bmp, t_bxpm *bxpm, char *path, char *name)
{
	free(bxpm->clr);
	free(bxpm->pix);
	free(bxpm);
	free(bmp->data);
	free(path);
	free(name);
}

int	main(int ac, char **av)
{
	int		i;
	t_bmp	bmp[1];
	t_bxpm	*bxpm;
	char	*path;
	char	*name;

	i = 0;
	if (ac == 1)
		return (1);
	while (++i < ac)
	{
		if (!ft_strequ(&av[i][ft_strlen(av[i]) - 4], ".bmp"))
			continue ;
		read_bmp(&bmp[0], av[i]);
		bxpm = bmp_to_bxpm(bmp);
		ft_printf("Reading\t%s\n", av[i]);
		create_path_and_name(av[i], &path, &name);
		ft_printf("Writing\t%s.bxpm\n", path);
		write_bxpm2(bxpm, path, "test");
		ft_printf("{GREEN}Done with: %s{RESET}\n", path);
		free_converter(bmp, bxpm, path, name);
	}
	return (0);
}
