/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:12:41 by mishin            #+#    #+#             */
/*   Updated: 2021/09/15 16:28:19 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*make_forks(int num_philos)
{
	pthread_mutex_t	*forks;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!forks)
		return (NULL);
	printf("forks origin = %p\n", forks);
	while (--num_philos >= 0)
		pthread_mutex_init(&forks[num_philos], NULL);
	return (forks);
}

int	get_fork(t_philo *philo, int direction)
{
	if (direction == LEFT)
		timestamp(philo, "take left fork");
	else if (direction == RIGHT)
		timestamp(philo, "take right fork");
	else
		return (0);
	return (1);
}
