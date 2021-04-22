
#include "doom.h"

void	if_norm(char *file_name, t_bxpm *bxpm)
{
	int fd;
	char *line;
	char **arr;
	int y = 1;
	int i;

	if (!(fd = open(file_name, O_RDONLY)))
		ft_printf("ERERERERER\n");
	get_next_line(fd, &line);
	ft_strdel(&line);
	y = 1;
	while (get_next_line(fd, &line))
	{
		if (y > 1)
		{
			ft_strdel(&line);
			break ;
		}
		arr = ft_strsplit(line, ',');
		bxpm->w = ft_atoi(arr[0]);
		bxpm->h = ft_atoi(arr[1]);
		bxpm->clr_nb = ft_atoi(arr[2]);
		bxpm->pix_nb = ft_atoi(arr[3]);
		i = 0;
		while (arr[i] != NULL)
		{
			ft_strdel(&arr[i]);
			i++;
		}
		free(arr);
		ft_strdel(&line);
		y++;
	}

	bxpm->clr = ft_memalloc(sizeof(uint32_t) * bxpm->clr_nb);

	int x = 0;
	y = 1;
	while (get_next_line(fd, &line))
	{
		if (x >= bxpm->clr_nb)
		{
			ft_strdel(&line);
			break ;
		}
		arr = ft_strsplit(line, ',');
		i = 0;
		while (arr[i] != NULL)
		{
			sscanf(arr[i], "%x", &bxpm->clr[x]);
			//bxpm->clr[x] = hexdec(arr[i]);
			ft_strdel(&arr[i]);
			i++;
			x++;
		}
		free(arr);
		ft_strdel(&line);
		y++;
	}

	bxpm->pix = ft_memalloc(sizeof(unsigned short) * bxpm->pix_nb);
	y = 1;
	x = 0;
	while (get_next_line(fd, &line))
	{
		if (x >= bxpm->pix_nb)
		{
			ft_strdel(&line);
			break ;
		}
		arr = ft_strsplit(line, ',');
		i = 0;
		while (arr[i] != NULL)
		{
			bxpm->pix[x] = ft_atoi(arr[i]);
			ft_strdel(&arr[i]);
			i++;
			x++;
		}
		free(arr);
		ft_strdel(&line);
		y++;
	}
	free(line);
	close(fd);
}
