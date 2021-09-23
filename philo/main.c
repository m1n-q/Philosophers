/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/23 19:11:03 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	*ph;
	t_philo			*philos;
	pthread_t		*monitor;
	int				i;

	i = 0;
	ll.head = NULL;
	ll.size = 0;
	if (input(&ll, argc, argv) == ERROR)
		return (ERROR);
	if (make_phmeta(ll, &ph))
		return (2);
	pthread_mutex_lock(ph->start);
	philos = make_philos(ph);
	if (!philos)
		return (3);
	i = -1;
	while (++i < ph->num_philos)
		pthread_detach(philos[i].tid);
	pthread_mutex_unlock(ph->start);
	monitor = make_monitor(philos);				//TODO: if no monitor, free previous allocated rsrcs
	pthread_join(*monitor, NULL);
	usleep(100000);
	release(philos, ph, monitor);				//TODO: 종료 시점 맞춰주기
}



	//ISSUE: ACCESSING PHILOS CAUSES SEGFAULT AFTER PTHREAD_JOIN
	//ISSUE: Value of var philos is changed after pthread_join
	/* ISSUE_CLOSED */
	/* void **retval of pthread_join() should be ptr to ptr(64-bit).
	/* integer 'exit' was 32-bit. so retval overwrites philos that follows 'exit' in memory. */

	//TODO: release all resources at exit
	//TODO: if error occured, free previous allocated resources
	//TODO: a philo died, simulation has to be terminated

	//FIXIT: printing order
