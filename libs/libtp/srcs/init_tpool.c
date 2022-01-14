/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tpool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:14:42 by nneronin          #+#    #+#             */
/*   Updated: 2021/07/31 14:11:04 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tpool.h"

int	tpool_add(t_tpool *tpool, int (*func)(void *), void *arg)
{
	t_task	*task;

	if (!func)
		return (tpool_error(-5));
	task = create_task(func, arg);
	if (!task)
		return (tpool_error(-4));
	pthread_mutex_lock(&tpool->mutex);
	if (tpool->tasks)
		task->next = tpool->tasks;
	tpool->tasks = task;
	pthread_cond_broadcast(&tpool->task_cond);
	pthread_mutex_unlock(&tpool->mutex);
	return (1);
}

t_task	*create_task(int (*func)(void*), void *arg)
{
	t_task	*new_task;

	if (!func)
		return (NULL);
	new_task = (t_task *)malloc(sizeof(t_task));
	if (!new_task)
		return (NULL);
	new_task->func = func;
	new_task->arg = arg;
	new_task->next = NULL;
	return (new_task);
}

int	init_tpool(t_tpool *tpool, int amount)
{
	int	i;

	i = -1;
	if (amount <= 0)
		return (tpool_error(-6));
	tpool_bzero(tpool, sizeof(t_tpool));
	pthread_mutex_init(&tpool->mutex, NULL);
	pthread_cond_init(&tpool->task_cond, NULL);
	pthread_cond_init(&tpool->main_cond, NULL);
	tpool->nb_threads = amount;
	tpool->threads = (pthread_t *)malloc(sizeof(pthread_t) * amount);
	if (!tpool->threads)
		return (tpool_error(-3));
	tpool_bzero(tpool->threads, sizeof(pthread_t) * amount);
	while (++i < amount)
		if (pthread_create(&tpool->threads[i], NULL, tpool_func, tpool))
			return (tpool_error(-2));
	pthread_mutex_lock(&tpool->mutex);
	while (tpool->alive_threads < tpool->nb_threads - 1)
		pthread_cond_wait(&tpool->main_cond, &tpool->mutex);
	pthread_mutex_unlock(&tpool->mutex);
	return (1);
}
