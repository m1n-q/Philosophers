/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:51:42 by mishin            #+#    #+#             */
/*   Updated: 2021/09/17 18:53:23 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

double	timestamp(t_philo *philo, char *msg)
{
	struct timeval	now;
	double			time_in_mill;

	if (msg)
	{
		gettimeofday(&now, NULL);
		time_in_mill = (now.tv_sec - philo->start->tv_sec) * 1000 + \
					(now.tv_usec - philo->start->tv_usec) / 1000;
		// pthread_mutex_lock(philo->info->print);
		printf("[%.0fms] %d %s\n", time_in_mill, philo->id, msg);
		// pthkread_mutex_unlock(philo->info->print);
	}
	else
	{
		gettimeofday(&now, NULL);
		time_in_mill = (now.tv_sec - philo->last_meal.time.tv_sec) * 1000 + \
					(now.tv_usec - philo->last_meal.time.tv_usec) / 1000;
	}
	return (time_in_mill);
}

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

void	msleep(t_philo *philo)
{
	timestamp(philo, "is sleeping");
	slp(philo->info->time_to_sleep);
	timestamp(philo, "is thinking");
	usleep(100);
}

//NOTE: cannot switching thread during "while" ? or monitoring thread fault ?
//NOTE: it does works w/o mutex(lastmeal)
void	slp(int ms)
{
	struct timeval	start;
	struct timeval	cur;

	gettimeofday(&start, NULL);
	gettimeofday(&cur, NULL);
	while ((cur.tv_sec - start.tv_sec) * 1000 + (cur.tv_usec - start.tv_usec) / 1000 < ms)
	{
		gettimeofday(&cur, NULL);
		usleep(100);
	}
}
