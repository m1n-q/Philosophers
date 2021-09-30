/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:48:24 by mishin            #+#    #+#             */
/*   Updated: 2021/09/30 21:20:51 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_philo			*philos;
	struct timeval	now;
	int				i;

	philos = (t_philo *)data;
	lock(philos->info->init);
	unlock(philos->info->init);
	if (philos->info->philos_error || philos->info->monitor_error)
		return (NULL);
	while (1)
	{
		i = -1;
		while (++i < philos->info->num_philos)
		{
			lock(&philos[i].last_meal.lock);
			if ((int)time_from(&(philos[i].last_meal.time), &now) \
													> philos->info->time_to_die)
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
		philos->info->monitor_error = ERROR;
		unlock(philos->info->init);
		if (check_terminated(philos))
		{
			free_all(philos, ph, monitor);
			return (NULL);
		}
	}
	philos->info->monitor_error = \
	pthread_create(monitor, NULL, monitoring, philos);
	return (monitor);
}
