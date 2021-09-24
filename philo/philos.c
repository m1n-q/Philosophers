/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 19:30:59 by mishin            #+#    #+#             */
/*   Updated: 2021/09/24 17:46:45 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_init_val	init_philos(t_philo_meta *ph)
{
	struct timeval	*start;
	t_time			*last_meals;
	pthread_mutex_t	*forks;
	int				i;

	forks = make_forks(ph->num_philos);
	start = (struct timeval *)malloc(sizeof(struct timeval));
	last_meals = (t_time *)malloc(sizeof(t_time) * ph->num_philos);
	if (!forks || !start || !last_meals)
	{
		release_rscs(forks, start, last_meals);
		return ((t_init_val){NULL, NULL, NULL});
	}
	i = -1;
	while (++i < ph->num_philos)
	{
		last_meals[i].time = *start;
		pthread_mutex_init(&(last_meals[i].lock), NULL);
	}
	ph->ptr_last_meals = last_meals;
	gettimeofday(start, NULL);
	return ((t_init_val){forks, start, last_meals});
}

t_philo	*make_philos(t_philo_meta *ph)
{
	t_philo			*philos;
	t_init_val		init_val;
	int				error;
	int				i;

	init_val = init_philos(ph);
	philos = (t_philo *)malloc(sizeof(t_philo) * ph->num_philos);
	if (!init_val.forks || !philos)
		return (release_rscs(init_val.forks, init_val.start, init_val.last_meals));
	i = -1;
	while (++i < ph->num_philos)
	{
		philos[i].start = init_val.start;
		philos[i].forks = init_val.forks;
		philos[i].last_meal = init_val.last_meals[i];
		philos[i].info = ph;
		philos[i].id = i + 1;
	}
	i = -1;
	error = 0;
	while (++i < ph->num_philos && !error)
		error = pthread_create(&philos[i].tid, NULL, dining, &philos[i]);
	if (error)
		return (release_rscs(init_val.forks, init_val.start, init_val.last_meals));
	return (philos);
}

static t_philo_meta		*init_phmeta(void)
{
	t_philo_meta	*ph;

	ph = (t_philo_meta *)malloc(sizeof(t_philo_meta));
	if (!ph)
		return (release_ph(ph));
	ph->someone_died = 0;
	ph->start = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	ph->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!ph->start || !ph->print)
		return (release_ph(ph));
	pthread_mutex_init(ph->start, NULL);
	pthread_mutex_init(ph->print, NULL);
	return (ph);
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

int	make_phmeta(t_ll_meta ll, t_philo_meta **ptr_ph)
{
	t_philo_meta	*ph;

	ph = init_phmeta();
	if (!ph)
		return (ll_clear(&ll.head));
	ll_to_phmeta(ll, ph);
	*ptr_ph = ph;
	return (0);
}
