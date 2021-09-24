/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/25 02:41:44 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_philo	*init(t_philo_meta *ph)
{
	t_philo	*philos;
	int			i;

	lock(ph->init);
	philos = make_philos(ph);
	if (!philos)
		return (NULL);			//TODO: if no philos, free all
	i = -1;
	while (++i < ph->num_philos)
		pthread_detach(philos[i].tid);
	unlock(ph->init);
	return (philos);
}

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	*ph;
	t_philo			*philos;
	pthread_t		*monitor;
	// int				i;

	ll.head = NULL;
	ll.size = 0;
	if (input(&ll, argc, argv) == ERROR)
		return (1);
	if (make_phmeta(ll, &ph))
		return (2);
	philos = init(ph);
	monitor = make_monitor(philos);
	pthread_join(*monitor, NULL);
	usleep(200 * 1000);
	free_all(philos, ph, monitor);
}
//TODO: free all resources at exit
//TODO: if no monitor, free all -> have to send signal to deatached threads
