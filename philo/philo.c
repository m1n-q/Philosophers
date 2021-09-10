/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/10 18:24:10 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *tmp(void *data)
{
	t_philo *philo;

	philo = ((t_philo *)data);
	if (last(philo))
	{
		pthread_mutex_lock(&philo->forks[right(philo)]);
			get_fork(philo, RIGHT);
			pthread_mutex_lock(&philo->forks[left(philo)]);
				get_fork(philo, LEFT);
				eat(philo);
			pthread_mutex_unlock(&philo->forks[left(philo)]);
		pthread_mutex_unlock(&philo->forks[right(philo)]);
		return (NULL);
	}

	pthread_mutex_lock(&philo->forks[left(philo)]);
		get_fork(philo, LEFT);
		pthread_mutex_lock(&philo->forks[right(philo)]);
			get_fork(philo, RIGHT);
			eat(philo);
		pthread_mutex_unlock(&philo->forks[right(philo)]);
	pthread_mutex_unlock(&philo->forks[left(philo)]);

	return (NULL);
}

t_philo	*make_philos(t_philo_meta *ph)
{
	t_philo			*philos;
	struct timeval	*start;
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
	if (gettimeofday(start, NULL))
		return (NULL);
	i = -1;
	while (++i < *(ph->num_philos))
	{
		philos[i].start = start;
		philos[i].forks = forks;
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

int	left(t_philo *philo)
{
	return (philo->id - 1);
}

int	right(t_philo *philo)
{
	return (philo->id % *(philo->info->num_philos));
}

void eat(t_philo *philo)
{
	timestamp(philo, "is eating");
	usleep(*(philo->info->time_to_eat) * 1000);
}

int	last(t_philo *philo)
{
	return (philo->id == *(philo->info->num_philos));
}
