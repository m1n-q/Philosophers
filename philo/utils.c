/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:51:42 by mishin            #+#    #+#             */
/*   Updated: 2021/09/11 15:33:42 by mishin           ###   ########.fr       */
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
		printf("[%.0fms] %d %s\n", time_in_mill, philo->id, msg);
	}
	else
	{
		gettimeofday(&now, NULL);
		time_in_mill = (now.tv_sec - philo->last_meal.tv_sec) * 1000 + \
					(now.tv_usec - philo->last_meal.tv_usec) / 1000;
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

void eat(t_philo *philo)
{
	gettimeofday(&(philo->last_meal), NULL);
	timestamp(philo, "is eating");
	usleep(*(philo->info->time_to_eat) * 1000);
}

int	last(t_philo *philo)
{
	return (philo->id == *(philo->info->num_philos));
}

void	msleep(t_philo *philo)
{
	timestamp(philo, "is sleeping");
	usleep(*(philo->info->time_to_sleep) * 1000);
	timestamp(philo, "is thinking");
}
