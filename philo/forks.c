/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 19:12:41 by mishin            #+#    #+#             */
/*   Updated: 2021/09/27 23:15:50 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_till(int cur_index, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < cur_index)
		pthread_mutex_destroy(&forks[i]);
}

pthread_mutex_t	*init_forks(int num_philos)
{
	pthread_mutex_t	*forks;
	int				error;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!forks)
		return (NULL);
	i = -1;
	error = 0;
	while (++i < num_philos)
	{
		error = pthread_mutex_init(&forks[i], NULL);
		if (error)
		{
			destroy_till(i, forks);
			return (NULL);
		}
	}
	return (forks);
}

void	get_fork(t_philo *philo, int direction)
{
	if (direction == LEFT)
		timestamp(philo, "take left fork");
	else if (direction == RIGHT)
		timestamp(philo, "take right fork");
}
