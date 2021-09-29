/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:52:29 by mishin            #+#    #+#             */
/*   Updated: 2021/09/29 19:16:21 by mishin           ###   ########.fr       */
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

	philo = (t_philo *)data;
	must_eat = philo->info->must_eat;
	lock(philo->info->init);
	unlock(philo->info->init);
	if (philo->id % 2 == 1)
		usleep(philo->info->time_to_eat * 1000); //FIXIT : set properly (what if odd philos)
	while (must_eat--)
	{
		if (philo->info->someone_died || \
			philo->info->create_philo_error || \
			philo->info->create_monitor_error)
		{
			philo->terminated = 1;
			printf("%d\n", philo->terminated);
			return (NULL);
		}
		if (!last(philo))
			leftright(philo);
		else
			rightleft(philo);
	}
	return (NULL);
}
//FIXIT: num == 1, a philo should died
