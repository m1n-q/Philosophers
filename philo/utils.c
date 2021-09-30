/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:51:42 by mishin            #+#    #+#             */
/*   Updated: 2021/09/30 15:26:46 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	left(t_philo *philo)
{
	return (philo->id - 1);
}

int	right(t_philo *philo)
{
	return (philo->id % philo->info->num_philos);
}

int	last(t_philo *philo)
{
	return (philo->id == philo->info->num_philos);
}

void	msleep(double ms)
{
	struct timeval	start;
	struct timeval	cur;

	gettimeofday(&start, NULL);
	while (!gettimeofday(&cur, NULL) && \
		(cur.tv_sec - start.tv_sec) * 1000.0 + \
		(cur.tv_usec - start.tv_usec) / 1000.0 <= ms)
		usleep(200);
}
//FIXIT: vary with num_philos, and test large case lag

int	check_terminated(t_philo *philos)
{
	int	i;
	int	total_terminated;

	total_terminated = 0;
	while (total_terminated != philos->info->total_created)
	{
		total_terminated = 0;
		i = -1;
		while (++i < philos->info->num_philos)
			total_terminated += philos[i].terminated;
	}
	return (1);
}
