/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/07 20:26:35 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ll_to_ph(t_ll_handler ll, t_philo_handler *ph)
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
		{
			if (cur)
				ph->must_eat = (int)cur->data;
			else
				ph->must_eat = -1;
			break ;
		}
		cur = cur->next;
	}
}

void	*tmp(void *data)
{
	printf("thread : %d created\n", ((t_philo *)data)->id);
	return (NULL);
}

t_philo	*make_philos(t_philo_handler ph)
{
	t_philo	*philos;
	int		i;
	int		error;

	philos = (t_philo *)malloc(sizeof(t_philo) * ph.num_philos);
	if (!philos)
		return (NULL);
	i = -1;
	while (++i < ph.num_philos)
	{
		error = pthread_create(&philos[i].tid, NULL, tmp, &philos[i]);
		if (error)
			return (NULL);	//TODO: free all philos / threads
		philos[i].id = i + 1;
	}
	return (philos);
}
