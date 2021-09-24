/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:52:29 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 18:22:09 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	eat(t_philo *philo)
{
	lock(&philo->last_meal.lock);
	gettimeofday(&(philo->last_meal.time), NULL);
	timestamp(philo, "is eating");
	unlock(&philo->last_meal.lock);
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
	int		must_eat;

	philo = ((t_philo *)data);
	must_eat = philo->info->must_eat;
	if (philo->id % 2 == 1)
		usleep(60 * 1000);
	lock(philo->info->start);
	unlock(philo->info->start);
	while (must_eat--)
	{
		if (philo->info->someone_died)
			return (NULL);
		if (!last(philo))
			leftright(philo);
		else
			rightleft(philo);
	}
	return (NULL);
}
