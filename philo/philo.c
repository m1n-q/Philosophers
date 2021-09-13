/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/14 00:26:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*make_philos(t_philo_meta *ph)
{
	t_philo			*philos;
	struct timeval	*start;
	t_time			*last_meals;
	pthread_mutex_t	*forks;
	int				error;
	int				i;

	philos = (t_philo *)malloc(sizeof(t_philo) * *(ph->num_philos));
	if (!philos)
		return (NULL);
	forks = make_forks(*(ph->num_philos));
	if (!forks)
		return (NULL);
	start = (struct timeval *)malloc(sizeof(struct timeval));
	if (!start)
		return (NULL);
	last_meals = (t_time *)malloc(sizeof(t_time) * *(ph->num_philos));
	if (!last_meals)
		return (NULL);
	gettimeofday(start, NULL);
	i = -1;
	while (++i < *(ph->num_philos))
	{
		last_meals[i].time = *start;
		pthread_mutex_init(&(last_meals[i].lock), NULL);
	}
	i = -1;
	while (++i < *(ph->num_philos))
	{
		philos[i].start = start;
		philos[i].last_meal = last_meals[i];
		philos[i].forks = forks;
		philos[i].info = ph;
		philos[i].id = i + 1;
	}
	i = -1;
	while (++i < *(ph->num_philos))
	{
		error = pthread_create(&philos[i].tid, NULL, dining, &philos[i]);
		if (error)
			return (NULL);
	}
	return (philos);
}

static inline void	eat(t_philo *philo)
{
	// double tm;

	// tm = timestamp(philo, NULL);
	gettimeofday(&(philo->last_meal.time), NULL);
	timestamp(philo, "is eating");
	// printf("%.0f\n", tm);
	usleep(*(philo->info->time_to_eat) * 1000);
}

static inline void	leftright(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[left(philo)]);
	get_fork(philo, LEFT);
	pthread_mutex_lock(&philo->forks[right(philo)]);
	get_fork(philo, RIGHT);
	pthread_mutex_lock(&philo->last_meal.lock);
	eat(philo);
	pthread_mutex_unlock(&philo->last_meal.lock);
	pthread_mutex_unlock(&philo->forks[right(philo)]);
	pthread_mutex_unlock(&philo->forks[left(philo)]);
	msleep(philo);
}

static inline void	rightleft(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[right(philo)]);
	get_fork(philo, RIGHT);
	pthread_mutex_lock(&philo->forks[left(philo)]);
	get_fork(philo, LEFT);
	pthread_mutex_lock(&philo->last_meal.lock);
	eat(philo);
	pthread_mutex_unlock(&philo->last_meal.lock);
	pthread_mutex_unlock(&philo->forks[left(philo)]);
	pthread_mutex_unlock(&philo->forks[right(philo)]);
	msleep(philo);
}

void	*dining(void *data)
{
	t_philo	*philo;
	int		must_eat;

	philo = ((t_philo *)data);
	must_eat = *(philo->info->must_eat);
	while (must_eat--)
	{
		if (philo->id % 2 == 1)	//TODO: dicided by num_philos ( even / odd )?
			usleep(800);
		if (!last(philo))
			leftright(philo);
		else
			rightleft(philo);
	}
	return (NULL);
}
