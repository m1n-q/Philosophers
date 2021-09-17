/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:48:24 by mishin            #+#    #+#             */
/*   Updated: 2021/09/17 17:29:29 by mishin           ###   ########.fr       */
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
				timestamp(&philos[i], "is died");
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
