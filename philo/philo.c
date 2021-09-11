/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/11 15:32:48 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *tmp(void *data)
{
	t_philo *philo;
	int		must_eat;

	philo = ((t_philo *)data);
	must_eat = *(philo->info->must_eat);
	while (must_eat--)
	{
		if (philo->id % 2 == 1)	//TODO: dicided by num_philos ( even / odd )?
			usleep(350);

		if (last(philo))
		{
			pthread_mutex_lock(&philo->forks[right(philo)]);
				get_fork(philo, RIGHT);
				pthread_mutex_lock(&philo->forks[left(philo)]);
					get_fork(philo, LEFT);
					pthread_mutex_lock(&philo->eating[philo->id - 1]);
					eat(philo);
					pthread_mutex_unlock(&philo->eating[philo->id - 1]);
				pthread_mutex_unlock(&philo->forks[left(philo)]);
			pthread_mutex_unlock(&philo->forks[right(philo)]);
			msleep(philo);
		}
		else
		{
			pthread_mutex_lock(&philo->forks[left(philo)]);
				get_fork(philo, LEFT);
				pthread_mutex_lock(&philo->forks[right(philo)]);
					get_fork(philo, RIGHT);
					pthread_mutex_lock(&philo->eating[philo->id - 1]);
					eat(philo);
					pthread_mutex_unlock(&philo->eating[philo->id - 1]);
				pthread_mutex_unlock(&philo->forks[right(philo)]);
			pthread_mutex_unlock(&philo->forks[left(philo)]);
			msleep(philo);
		}
	}

	return (NULL);
}

t_philo	*make_philos(t_philo_meta *ph)
{
	t_philo			*philos;
	struct timeval	*start;
	struct timeval	*last_meals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*eating;
	int				error;
	int				i;

	philos = (t_philo *)malloc(sizeof(t_philo) * *(ph->num_philos));
	if (!philos)
		return (NULL);
	forks = make_forks(*(ph->num_philos));
	if (!forks)
		return (NULL);
	eating = make_eating(*(ph->num_philos));
	if (!eating)
		return (NULL);
	start = (struct timeval *)malloc(sizeof(struct timeval));
	if (!start)
		return (NULL);
	last_meals = (struct timeval *)malloc(sizeof(struct timeval) * *(ph->num_philos));
	if (!last_meals)
		return (NULL);
	if (gettimeofday(start, NULL))
		return (NULL);
	i = -1;
	while (++i < *(ph->num_philos))
		last_meals[i] = *start;
	i = -1;
	while (++i < *(ph->num_philos))
	{
		philos[i].start = start;
		philos[i].last_meal = last_meals[i];
		philos[i].forks = forks;
		philos[i].eating = eating;
		philos[i].info = ph;
		philos[i].id = i + 1;
	}
	i = -1;
	while (++i < *(ph->num_philos))
	{
		error = pthread_create(&philos[i].tid, NULL, tmp, &philos[i]);
		if (error)
			return (NULL);
	}
	return (philos);
}

void	*monitoring(void *data)
{
	t_philo	*philos;
	int		i;

	//printf("monitoring philo %d : [%.0fms]\n", philos[i].id, timestamp(&philos[i], NULL)) &&
	philos = (t_philo *)data;
	while (1)
	{
		i = -1;
		while (++i < *(philos[0].info->num_philos))
		{
			pthread_mutex_lock(&(philos[i].eating[philos[i].id-1]));
			if ((int)timestamp(&philos[i], NULL) > *(philos[0].info->time_to_die) && timestamp(&philos[i], "is died"))
				return (NULL);
			pthread_mutex_unlock(&(philos[i].eating[philos[i].id-1]));
		}
	}
}

pthread_t *make_monitor(t_philo *philos)
{
	pthread_t	*monitor;
	int			error;

	monitor = (pthread_t *)malloc(sizeof(pthread_t));
	if (!monitor)
		return (NULL);
	error = pthread_create(monitor, NULL, monitoring, philos);
	if (error)
		return (NULL);
	return (monitor);
}


