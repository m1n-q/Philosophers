/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:57:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 17:47:12 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************ */
/*                          */
/*   reclaimed resources    */
/*                          */
/*	- philo & meta          */
/*                          */
/*	- mutex (fork)          */
/*	- mutex (lastmeal.lock) */
/*	- mutex (ph->init)      */
/*	- mutex (ph->print)     */
/*                          */
/*	- timeval (ph->start)   */
/*	- t_time (ph->lastmeal) */
/*	- forks                 */
/*		                    */
/*	- linked list           */
/*	- monitor (joined)      */
/*	- threads (detached)    */
/*                          */
/* ************************ */

static void	destroy_till(int cur_index, t_time *last_meals)
{
	int	i;

	i = -1;
	while (++i < cur_index)
		pthread_mutex_destroy(&last_meals[i].lock);
}

void	*free_forks(pthread_mutex_t *forks)
{
	if (forks)
		free(forks);
	return (NULL);
}

void	free_philos(t_philo *philos)
{
	int	num_philos;
	int	i;

	num_philos = philos[0].info->num_philos;
	i = -1;
	while (++i < num_philos)
		pthread_mutex_destroy(&philos->forks[i]);
	free(philos->forks);
	free(philos);
}

int	free_phmeta(t_philo_meta *ph)
{
	if (ph->start)
		free(ph->start);
	if (ph->init)
		free(ph->init);
	if (ph->print)
		free(ph->print);
	if (ph->ptr_last_meals)
		free(ph->ptr_last_meals);
	free(ph);
	return (-1);
}

void	destroy_meta_mutex(t_philo_meta *ph)
{
	pthread_mutex_destroy(ph->init);
	pthread_mutex_destroy(ph->print);
	destroy_till(ph->num_philos, ph->ptr_last_meals);
}

void	free_all(t_philo *philos, t_philo_meta *ph, pthread_t *monitor)
{
	free_philos(philos);
	destroy_meta_mutex(ph);
	free_phmeta(ph);
	if (monitor)
		free(monitor);
}
