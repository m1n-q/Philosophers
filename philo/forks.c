/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:12:41 by mishin            #+#    #+#             */
/*   Updated: 2021/09/23 11:34:02 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*make_forks(int num_philos)
{
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!forks)
		return (NULL);
	while (--num_philos >= 0)
		pthread_mutex_init(&forks[num_philos], NULL);
	return (forks);
}

double	get_fork(t_philo *philo, int direction)
{
	double	status;

	status = 0.0;
	if (direction == LEFT)
		status = timestamp(philo, "take left fork");
	else if (direction == RIGHT)
		status = timestamp(philo, "take right fork");
	return (status);
}
