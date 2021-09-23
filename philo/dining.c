/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:52:29 by mishin            #+#    #+#             */
/*   Updated: 2021/09/23 18:36:33 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal.lock);
	gettimeofday(&(philo->last_meal.time), NULL);
	timestamp(philo, "is eating");
	pthread_mutex_unlock(&philo->last_meal.lock);
	msleep(philo->info->time_to_eat);
}

static inline void	sleep_think(t_philo *philo)
{
	timestamp(philo, "is sleeping");
	msleep(philo->info->time_to_sleep);
	timestamp(philo, "is thinking");
	usleep(100);
}

static inline void	leftright(t_philo *philo)
{
	pthread_mutex_lock(&(philo->forks[left(philo)]));
	get_fork(philo, LEFT);
	pthread_mutex_lock(&(philo->forks[right(philo)]));
	get_fork(philo, RIGHT);
	eat(philo);
	pthread_mutex_unlock(&(philo->forks[right(philo)]));
	pthread_mutex_unlock(&(philo->forks[left(philo)]));
	sleep_think(philo);
}

static inline void	rightleft(t_philo *philo)
{
	pthread_mutex_lock(&(philo->forks[right(philo)]));
	get_fork(philo, RIGHT);
	pthread_mutex_lock(&(philo->forks[left(philo)]));
	get_fork(philo, LEFT);
	eat(philo);
	pthread_mutex_unlock(&(philo->forks[left(philo)]));
	pthread_mutex_unlock(&(philo->forks[right(philo)]));
	sleep_think(philo);
}

void	*dining(void *data)
{
	t_philo	*philo;
	int		must_eat;

	philo = ((t_philo *)data);
	must_eat = philo->info->must_eat;
	if (philo->id % 2 == 1)
		usleep(60 * 1000);
	pthread_mutex_lock(philo->info->start);
	pthread_mutex_unlock(philo->info->start);
	while (must_eat--)
	{
		pthread_mutex_lock(philo->info->dying);
		if (philo->info->someone_died)
			return (NULL);
		pthread_mutex_unlock(philo->info->dying);
		if (!last(philo))
			leftright(philo);
		else
			rightleft(philo);
	}
	return (NULL);
}

//NOTE: it will not print even without dying lock
