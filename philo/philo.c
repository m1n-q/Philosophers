/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/22 17:24:03 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_init_val	init_philos(t_philo_meta *ph)
{
	struct timeval	*start;
	t_time			*last_meals;
	pthread_mutex_t	*forks;
	int				i;

	forks = make_forks(ph->num_philos);
	start = (struct timeval *)malloc(sizeof(struct timeval));
	last_meals = (t_time *)malloc(sizeof(t_time) * ph->num_philos);
	if (!forks || !start || !last_meals)
	{
		release_rscs(forks, start, last_meals);
		return ((t_init_val){NULL, NULL, NULL});
	}
	i = -1;
	while (++i < ph->num_philos)
	{
		last_meals[i].time = *start;
		pthread_mutex_init(&(last_meals[i].lock), NULL);
	}
	ph->ptr_last_meals = last_meals;
	gettimeofday(start, NULL);
	return ((t_init_val){forks, start, last_meals});
}

t_philo	*make_philos(t_philo_meta *ph)
{
	t_philo			*philos;
	t_init_val		init_val;
	int				error;
	int				i;

	init_val = init_philos(ph);
	philos = (t_philo *)malloc(sizeof(t_philo) * ph->num_philos);
	if (!init_val.forks || !philos)
		return (release_rscs(init_val.forks, init_val.start, init_val.last_meals));
	i = -1;
	while (++i < ph->num_philos)
	{
		philos[i].start = init_val.start;
		philos[i].forks = init_val.forks;
		philos[i].last_meal = init_val.last_meals[i];
		philos[i].info = ph;
		philos[i].id = i + 1;
	}
	i = -1;
	error = 0;
	while (++i < ph->num_philos && !error)
		error = pthread_create(&philos[i].tid, NULL, dining, &philos[i]);
	if (error)
		return (release_rscs(init_val.forks, init_val.start, init_val.last_meals));
	return (philos);
}

static inline void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->last_meal.lock);
	gettimeofday(&(philo->last_meal.time), NULL);
	// pthread_mutex_unlock(&philo->last_meal.lock);
	timestamp(philo, "is eating");

	msleep(philo->info->time_to_eat);
	// usleep(1000 * philo->info->time_to_eat);
}

static inline void	sleep_think(t_philo *philo)
{
	timestamp(philo, "is sleeping");

	msleep(philo->info->time_to_sleep);
	// usleep(1000 * philo->info->time_to_sleep);


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
		if (!last(philo))
			leftright(philo);
		else
			rightleft(philo);
	}
	return (NULL);
}
