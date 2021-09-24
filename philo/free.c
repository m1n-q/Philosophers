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

/* *********************** */
/*                         */
/*   reclaimed resources   */
/*                         */
/*	- philo & meta         */
/*	- mutex (fork)         */
/*	- mutex (lastmeal)     */
/*	- mutex (ph->init)     */
/*	- mutex (ph->print)    */
/*                         */
/*	- timeval (start)      */
/*	- t_time (lastmeal)    */
/*	- forks                */
/*		                   */
/*	- linked list          */
/*	- monitor (joined)     */
/*	- threads (detached)   */
/*                         */
/* *********************** */

void	*free_rscs(pthread_mutex_t *forks, struct timeval *start, \
				t_time *lastmeals)
{
	if (forks)
		free(forks);
	if (start)
		free(start);
	if (lastmeals)
		free(lastmeals);
	return (NULL);
}

static void	free_philos(t_philo *philos)
{
	int	num_philos;
	int	i;

	num_philos = philos[0].info->num_philos;
	i = -1;
	while (++i < num_philos)
	{
		pthread_mutex_destroy(&philos[0].forks[i]);
		pthread_mutex_destroy(&philos[i].last_meal.lock);
	}
	free(philos[0].forks);
	free(philos[0].start);
	free(philos);
}

void	*free_phmeta(t_philo_meta *ph)
{
	if (ph->ptr_last_meals)
		free(ph->ptr_last_meals);
	if (ph->init)
	{
		pthread_mutex_destroy(ph->init);
		free(ph->init);
	}
	if (ph->print)
	{
		pthread_mutex_destroy(ph->print);
		free(ph->print);
	}
	free(ph);
	return (NULL);
}

void	free_all(t_philo *philos, t_philo_meta *ph, pthread_t *monitor)
{
	free_philos(philos);
	free_phmeta(ph);
	free(monitor);
}
