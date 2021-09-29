/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:48:24 by mishin            #+#    #+#             */
/*   Updated: 2021/09/29 14:05:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_philo			*philos;
	double			time_in_mill;
	struct timeval	now;
	int				i;

	philos = (t_philo *)data;
	lock(philos[0].info->init);
	unlock(philos[0].info->init);
	if (philos->info->create_philo_error || philos->info->create_monitor_error)
		return (NULL);
	while (1)
	{
		i = -1;
		while (++i < philos[0].info->num_philos)
		{
			lock(&philos[i].last_meal.lock);
			time_in_mill = time_from(&(philos[i].last_meal.time), &now);
			if ((int)time_in_mill > philos[0].info->time_to_die)
			{
				timestamp(&philos[i], "is \e[91mdied\e[0m");
				unlock(&philos[i].last_meal.lock);
				return (NULL);
			}
			unlock(&philos[i].last_meal.lock);
		}
	}
}

pthread_t	*make_monitor(t_philo *philos, t_philo_meta *ph)
{
	pthread_t	*monitor;

	monitor = (pthread_t *)malloc(sizeof(pthread_t));
	if (!monitor)
	{
		// philos->info->create_monitor_error = ERROR;
		unlock(philos->info->init);
		if (check_terminated(philos))
		{
			free_philos(philos);
			destroy_meta_mutex(ph);
			free_phmeta(ph);
			return (NULL);
		}
	}
	philos->info->create_monitor_error = \
	pthread_create(monitor, NULL, monitoring, philos);
	return (monitor);
}
