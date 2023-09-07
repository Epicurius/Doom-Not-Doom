/*
 * -*- coding: utf-8 -*-
 * vim: ts=4 sw=4 tw=80 et ai si
 *
 * Author: Niklas Neronin <niklas.neronin@gmail.com>
 */

#include "tpool.h"

t_task	*get_task(t_tpool *tpool)
{
	t_task	*task;

	if (!tpool || !tpool->tasks)
		return (0);
	task = tpool->tasks;
	tpool->tasks = tpool->tasks->next;
	if (!tpool->tasks)
		pthread_cond_signal(&tpool->main_cond);
	return (task);
}

void	do_task(t_tpool *tpool)
{
	t_task	*task;

	task = get_task(tpool);
	tpool->running_threads += 1;
	pthread_mutex_unlock(&tpool->mutex);
	if (!task->func(task->arg))
		tpool->error = 1;
	if (task)
	{
		free(task);
		task = NULL;
	}
	pthread_mutex_lock(&tpool->mutex);
	tpool->running_threads -= 1;
	if (!tpool->tasks && tpool->running_threads == 0 && !tpool->stop)
		pthread_cond_signal(&tpool->main_cond);
	pthread_mutex_unlock(&tpool->mutex);
}

void	*tpool_func(void *arg)
{
	int		id;
	t_tpool	*tpool;

	tpool = (t_tpool *)arg;
	pthread_mutex_lock(&tpool->mutex);
	id = tpool->alive_threads;
	tpool->alive_threads += 1;
	if (id == (tpool->nb_threads - 1))
		pthread_cond_signal(&tpool->main_cond);
	pthread_mutex_unlock(&tpool->mutex);
	while (!tpool->stop)
	{
		pthread_mutex_lock(&tpool->mutex);
		while (!tpool->tasks && !tpool->stop)
			pthread_cond_wait(&tpool->task_cond, &tpool->mutex);
		if (tpool->stop)
			continue ;
		do_task(tpool);
	}
	tpool->alive_threads -= 1;
	if (!tpool->tasks && tpool->alive_threads == 0 && tpool->stop)
		pthread_cond_signal(&tpool->main_cond);
	pthread_mutex_unlock(&tpool->mutex);
	return (0);
}

int	tpool_wait(t_tpool *tpool)
{
	if (!tpool)
		return (1);
	pthread_mutex_lock(&tpool->mutex);
	while ((!tpool->stop && tpool->running_threads > 0)
		|| (tpool->stop && tpool->alive_threads > 0)
		|| tpool->tasks)
		pthread_cond_wait(&tpool->main_cond, &tpool->mutex);
	pthread_mutex_unlock(&tpool->mutex);
	if (tpool->error)
		return (tpool_error(-1));
	return (1);
}
