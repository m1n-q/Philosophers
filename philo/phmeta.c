/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmeta.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 23:17:25 by mishin            #+#    #+#             */
/*   Updated: 2021/09/30 13:35:27 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_last_meals(t_time *last_meals, int num)
{
	int	i;
	int	error;

	i = -1;
	while (++i < num)
	{
		error = pthread_mutex_init(&last_meals[i].lock, NULL);
		if (error)
		{
			destroy_till(i, last_meals, "t_time");
			return (ERROR);
		}
	}
	return (0);
}

static void	ll_to_phmeta(t_ll_meta ll, t_philo_meta *ph)
{
	t_ll	*cur;
	int		i;

	i = 0;
	cur = ll.head;
	while (++i)
	{
		if (i == 1)
			ph->num_philos = (int)cur->data;
		else if (i == 2)
			ph->time_to_die = (int)cur->data;
		else if (i == 3)
			ph->time_to_eat = (int)cur->data;
		else if (i == 4)
			ph->time_to_sleep = (int)cur->data;
		else if (i == 5)
		{
			ph->must_eat = -1;
			if (cur)
				ph->must_eat = (int)cur->data;
			break ;
		}
		cur = cur->next;
	}
	ll_clear(&ll.head);
}

static t_philo_meta	*init_phmeta(t_ll_meta ll)
{
	t_philo_meta	*ph;

	ph = (t_philo_meta *)malloc(sizeof(t_philo_meta));
	if (!ph)
	{
		ll_clear(&ll.head);
		return (NULL);
	}
	ll_to_phmeta(ll, ph);
	ph->someone_died = 0;
	ph->init = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	ph->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	ph->start = (struct timeval *)malloc(sizeof(struct timeval));
	ph->ptr_last_meals = (t_time *)malloc(sizeof(t_time) * ph->num_philos);
	if (!ph->init || !ph->print || !ph->start || !ph->ptr_last_meals)
	{
		free_phmeta(ph);
		return (NULL);
	}
	ph->philos_error = 0;
	ph->monitor_error = 0;
	ph->total_created = 0;
	return (ph);
}

int	make_phmeta(t_ll_meta ll, t_philo_meta **ptr_ph)
{
	t_philo_meta	*ph;
	int				error;

	ph = init_phmeta(ll);
	if (!ph)
		return (ERROR);
	error = pthread_mutex_init(ph->init, NULL);
	if (error)
		return (free_phmeta(ph));
	error = pthread_mutex_init(ph->print, NULL);
	if (error)
	{
		pthread_mutex_destroy(ph->init);
		return (free_phmeta(ph));
	}
	error = init_last_meals(ph->ptr_last_meals, ph->num_philos);
	if (error)
	{
		pthread_mutex_destroy(ph->init);
		pthread_mutex_destroy(ph->print);
		return (free_phmeta(ph));
	}
	gettimeofday(ph->start, NULL);
	*ptr_ph = ph;
	return (0);
}
