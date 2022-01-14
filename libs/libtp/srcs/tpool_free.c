/*
 * https://github.com/Epicurius/Doom-Not-Doom
 * 
 * Created: 2020/11/09 10:36:46 nneronin
 * Updated: 2021/07/30 16:07:00 nneronin
 */

#include "tpool.h"

void	*tpool_bzero(void *arg, size_t n)
{
	size_t			i;
	char			*str;
	unsigned char	cchar;

	i = -1;
	str = arg;
	cchar = 0;
	while (++i < n)
		str[i] = cchar;
	return (arg);
}

void	tpool_memdel(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}

void	free_task_list(t_task *tasks)
{
	t_task	*tmp;

	while (tasks)
	{
		tmp = tasks->next;
		if (tasks)
		{
			free(tasks);
			tasks = NULL;
		}
		tasks = tmp;
	}
}

int	free_tpool(t_tpool *tpool)
{
	int		i;

	i = -1;
	if (!tpool->threads)
		return (0);
	pthread_mutex_lock(&tpool->mutex);
	free_task_list(tpool->tasks);
	tpool->stop = 1;
	pthread_cond_broadcast(&tpool->task_cond);
	pthread_mutex_unlock(&tpool->mutex);
	while (++i < tpool->nb_threads)
		if (pthread_join(tpool->threads[i], NULL))
			write(1, "Pthread_join error!\n", 20);
	tpool_memdel((void **)&tpool->threads);
	pthread_mutex_destroy(&tpool->mutex);
	pthread_cond_destroy(&tpool->task_cond);
	pthread_cond_destroy(&tpool->main_cond);
	return (0);
}
