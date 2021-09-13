/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 18:48:24 by mishin            #+#    #+#             */
/*   Updated: 2021/09/14 00:15:07 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *data)
{
	t_philo	*philos;
	int		i;
	// t_philo	*philo;

	// philo = (t_philo *)data;
	philos = (t_philo *)data;
	while (1)
	{
		i = -1;
		while (++i < *(philos[0].info->num_philos))
		{
			pthread_mutex_lock(&philos[i].last_meal.lock);
			if ((int)timestamp(&philos[i], NULL) > *philos[0].info->time_to_die \
			&& timestamp(&philos[i], "is died"))
				return (NULL);
			pthread_mutex_unlock(&philos[i].last_meal.lock);
		}
	}
	// while (1)
	// {
	// 	pthread_mutex_lock(&philo->last_meal.lock);
	// 	if ((int)timestamp(philo, NULL) > *(philo->info->time_to_die) \
	// 	&& timestamp(philo, "is died"))
	// 		return (NULL);
	// 	pthread_mutex_unlock(&philo->last_meal.lock);
	// }
}

pthread_t	*make_monitor(t_philo *philos)
{
	pthread_t	*monitor;
	int			error;
	int			i;

	monitor = (pthread_t *)malloc(sizeof(pthread_t) * *(philos[0].info->num_philos));
	if (!monitor)
		return (NULL);
	i = -1;
	while (++i < *(philos[0].info->num_philos))
	{
		error = pthread_create(monitor, NULL, monitoring, &philos[i]);
		if (error)
			return (NULL);
	}
	return (monitor);
}
