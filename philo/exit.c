/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:57:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/17 16:34:36 by mishin           ###   ########.fr       */
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

static void	release_philos(t_philo *philos)
{
	int	num_philos;
	int	i;


	num_philos = *(philos[0].info->num_philos);
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

static void	release_ph(t_philo_meta ph)
{
	free(ph.num_philos);
	free(ph.time_to_die);
	free(ph.time_to_eat);
	free(ph.time_to_sleep);
	free(ph.must_eat);
	free(ph.ptr_last_meals);
}

void	release(t_philo *philos, t_philo_meta ph, pthread_t *monitor)
{
	release_philos(philos);
	release_ph(ph);
	free(monitor);
}
