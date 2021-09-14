/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:51:42 by mishin            #+#    #+#             */
/*   Updated: 2021/09/15 01:14:07 by mishin           ###   ########.fr       */
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
		printf("%p | [%.0fms] %d %s\n", pthread_self(), time_in_mill, philo->id, msg);
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
	return (philo->id % *(philo->info->num_philos));
}

int	last(t_philo *philo)
{
	return (philo->id == *(philo->info->num_philos));
}

void	msleep(t_philo *philo)
{
	timestamp(philo, "is sleeping");
	// usleep(*(philo->info->time_to_sleep) * 1000);
	slp(*(philo->info->time_to_sleep));				//WARN: dyeing at 600ms
	timestamp(philo, "is thinking");
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
