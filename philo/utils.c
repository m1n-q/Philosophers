/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:51:42 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 18:15:37 by mishin           ###   ########.fr       */
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
