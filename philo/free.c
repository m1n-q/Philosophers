/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 13:57:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 17:47:12 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************ */
/*                          */
/*   reclaimed resources    */
/*                          */
/*	- philo & meta          */
/*                          */
/*	- mutex (fork)          */
/*	- mutex (lastmeal.lock) */
/*	- mutex (ph->init)      */
/*	- mutex (ph->print)     */
/*                          */
/*	- timeval (ph->start)   */
/*	- t_time (ph->lastmeal) */
/*	- forks                 */
/*		                    */
/*	- linked list           */
/*	- monitor (joined)      */
/*	- threads (detached)    */
/*                          */
/* ************************ */

void	destroy_till(int cur_index, void *arr, char *type)
{
	int				i;
	t_time			*last_meals;
	pthread_mutex_t	*forks;

	i = -1;
	if (!ft_strcmp(type, "t_time"))
	{
		last_meals = (t_time*)arr;
		while (++i < cur_index)
			pthread_mutex_destroy(&last_meals[i].lock);
	}
	else if (!ft_strcmp(type, "pthread_mutex_t"))
	{
		forks = (pthread_mutex_t *)arr;
		while (++i < cur_index)
			pthread_mutex_destroy(&forks[i]);
	}
	else
		printf("%s is not supported\n", type);
}

void	free_philos(t_philo *philos)
{
	int	num_philos;

	num_philos = philos[0].info->num_philos;
	destroy_till(num_philos, philos->forks, "pthread_mutex_t");
	free(philos->forks);
	free(philos);
}

int	free_phmeta(t_philo_meta *ph)
{
	free(ph->start);
	free(ph->init);
	free(ph->print);
	free(ph->ptr_last_meals);
	free(ph);
	return (ERROR);
}

void	destroy_meta_mutex(t_philo_meta *ph)
{
	pthread_mutex_destroy(ph->init);
	pthread_mutex_destroy(ph->print);
	destroy_till(ph->num_philos, ph->ptr_last_meals, "t_time");
}

void	free_all(t_philo *philos, t_philo_meta *ph, pthread_t *monitor)
{
	free_philos(philos);
	destroy_meta_mutex(ph);
	free_phmeta(ph);
	free(monitor);
}
