/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:51:42 by mishin            #+#    #+#             */
/*   Updated: 2021/09/20 16:23:34 by mishin           ###   ########.fr       */
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

		printf("\e[36m[%.0fms]\e[0m %d %s\n", time_in_mill, philo->id, msg);
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

//NOTE: cannot switching thread during "while" loop ?
//https://stackoverflow.com/questions/43419402/what-happens-when-you-write-a-simple-program-with-a-while1-loop-in-a-system-wi

//NOTE: mutex and context switching, (is busy waiting better?)

//

void	msleep(double ms)
{
	/*
	 * if #(threads) <= #(logical cores)
	 *     busy waiting
	 * else
	 *     sleep and awake
	 */

	struct timeval	start;
	struct timeval	cur;

	gettimeofday(&start, NULL);
	gettimeofday(&cur, NULL);
	while ((cur.tv_sec - start.tv_sec) * 1000 + (cur.tv_usec - start.tv_usec) / 1000 < ms)
	{
		// usleep(10);
		gettimeofday(&cur, NULL);
	}

	//NOTE: with large caese, usleep has better perfomance.
	// usleep(ms * 1000);
}
