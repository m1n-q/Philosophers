/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:48:24 by mishin            #+#    #+#             */
/*   Updated: 2021/09/22 18:00:32 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_philo	*philos;
	double	time_in_mill;
	int		i;

	philos = (t_philo *)data;
	while (1)
	{
		i = -1;
		while (++i < philos[0].info->num_philos)
		{
			pthread_mutex_lock(&philos[i].last_meal.lock);
			time_in_mill = (int)timestamp(&philos[i], NULL);
			if (time_in_mill > philos[0].info->time_to_die)
			{
				philos[0].info->someone_died = philos[i].id;
				timestamp(&philos[i], "is \e[91mdied\e[0m");
				pthread_mutex_unlock(&philos[i].last_meal.lock);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].last_meal.lock);
		}
	}
}


pthread_t	*make_monitor(t_philo *philos)
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

void	*monitoring_each(void *data)
{
	t_philo	*philo;
	int		from_lastmeal;

	philo = (t_philo *)data;
	while (1)
	{
		pthread_mutex_lock(&philo->last_meal.lock);
		from_lastmeal = (int)timestamp(philo, NULL);
		if (from_lastmeal > philo->info->time_to_die)
		{
			timestamp(philo, "is \e[91mdied\e[0m");
			pthread_mutex_unlock(&philo->last_meal.lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->last_meal.lock);
	}
}


pthread_t	*make_monitors(t_philo *philos)
{
	pthread_t	*monitors;
	int			error;
	int			i;

	monitors = (pthread_t *)malloc(sizeof(pthread_t) * philos[0].info->num_philos);
	if (!monitors)
		return (NULL);
	i = -1;
	error = 0;
	while (++i < philos[0].info->num_philos && !error)
		error = pthread_create(&monitors[i], NULL, monitoring_each, &philos[i]);
	if (error)
		return (NULL);
	return (monitors);
}


