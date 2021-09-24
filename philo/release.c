/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
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
/*	- mutex (meal)         */
/*	- timeval (start)      */
/*	- t_time (meal)        */
/*	- forks                */
/*		                   */
/*	- linked list          */
/*	- monitor (joined)     */
/*	- threads (detached)   */
/* *********************** */

void	*release_rscs(pthread_mutex_t *forks, struct timeval *start, t_time *lastmeals)
{
	if (forks)
		free(forks);
	if (start)
		free(start);
	if (lastmeals)
		free(lastmeals);
	return (NULL);
}

static void	release_philos(t_philo *philos)
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

void	*release_ph(t_philo_meta *ph)
{
	if (ph->ptr_last_meals)
		free(ph->ptr_last_meals);
	if (ph->start)
	{
		pthread_mutex_destroy(ph->start);
		free(ph->start);
	}
	if (ph->print)
	{
		pthread_mutex_destroy(ph->print);
		free(ph->print);
	}
	free(ph);
	return (NULL);
}

void	release(t_philo *philos, t_philo_meta *ph, pthread_t *monitor)
{
	release_philos(philos);
	release_ph(ph);
	free(monitor);
}
