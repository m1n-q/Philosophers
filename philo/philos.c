/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/29 18:42:48 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philos(t_philo_meta *ph)
{
	pthread_mutex_t	*forks;
	t_philo			*philos;
	int				i;

	forks = init_forks(ph->num_philos);
	if (!forks)
		return (NULL);
	philos = (t_philo *)malloc(sizeof(t_philo) * ph->num_philos);
	if (!philos)
	{
		destroy_till(ph->num_philos, forks, "pthread_mutex_t");
		free(forks);
		return (NULL);
	}
	i = -1;
	while (++i < ph->num_philos)
		philos[i].forks = forks;
	return (philos);
}

t_philo	*make_philos(t_philo_meta *ph)
{
	t_philo			*philos;
	int				i;

	philos = init_philos(ph);
	if (!philos)
	{
		unlock(ph->init);
		destroy_meta_mutex(ph);
		free_phmeta(ph);
		return (NULL);
	}
	i = -1;
	while (++i < ph->num_philos)
	{
		philos[i].last_meal = ph->ptr_last_meals[i];
		philos[i].last_meal.time = *(ph->start);
		philos[i].info = ph;
		philos[i].id = i + 1;
		philos[i].terminated = 0;
	}
	i = -1;
	while (!ph->create_philo_error && ++i < ph->num_philos)
		ph->create_philo_error = pthread_create(&philos[i].tid, NULL, dining, \
												&philos[i]);
	ph->total_created = i;
	return (philos);
}
