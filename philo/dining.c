/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:52:29 by mishin            #+#    #+#             */
/*   Updated: 2021/10/01 15:21:10 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	eat(t_philo *philo)
{
	lock(&philo->last_meal.lock);
	gettimeofday(&(philo->last_meal.time), NULL);
	timestamp(philo, "is eating");
	philo->must_eat--;
	unlock(&philo->last_meal.lock);
	msleep(philo->info->time_to_eat);
}

static inline void	sleep_think(t_philo *philo)
{
	timestamp(philo, "is sleeping");
	msleep(philo->info->time_to_sleep);
	timestamp(philo, "is thinking");
	usleep(200);
}

static inline void	leftright(t_philo *philo)
{
	lock(&(philo->forks[left(philo)]));
	get_fork(philo, LEFT);
	lock(&(philo->forks[right(philo)]));
	get_fork(philo, RIGHT);
	eat(philo);
	unlock(&(philo->forks[right(philo)]));
	unlock(&(philo->forks[left(philo)]));
	sleep_think(philo);
}

static inline void	rightleft(t_philo *philo)
{
	lock(&(philo->forks[right(philo)]));
	get_fork(philo, RIGHT);
	if (philo->info->num_philos == 1)
	{
		usleep(philo->info->time_to_die * 1050);
		unlock(&(philo->forks[right(philo)]));
		return ;
	}
	lock(&(philo->forks[left(philo)]));
	get_fork(philo, LEFT);
	eat(philo);
	unlock(&(philo->forks[left(philo)]));
	unlock(&(philo->forks[right(philo)]));
	sleep_think(philo);
}

void	*dining(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->must_eat = philo->info->must_eat;
	lock(philo->info->init);
	unlock(philo->info->init);
	if (philo->id % 2 == 1 && usleep(55 * philo->info->num_philos))
		if (!last(philo))
			usleep(55 * philo->info->num_philos);
	while (philo->must_eat)
	{
		if (philo->info->someone_died || \
			philo->info->philos_error || philo->info->monitor_error)
		{
			philo->terminated = 1;
			return (NULL);
		}
		if (!philo->id % 2)
			leftright(philo);
		else
			rightleft(philo);
	}
	philo->terminated = 1;
	return (NULL);
}

// 111 -> usleep(600)
// 200 -> usleep(10000)
