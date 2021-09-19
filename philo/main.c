/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/20 02:11:45 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	*ph;
	t_philo			*philos;
	// pthread_t		*monitor;
	pthread_mutex_t	*start;
	long long		exit;
	int				i;

	i = 0;
	exit = 1;
	ll.head = NULL;
	ll.size = 0;
	while (++i < argc)
		if (input_to_ll(&ll, argv[i]) == -1)
			return (1);
	if (ll.size != 4 && ll.size != 5)
		return (ll_clear(&ll.head));
	ph = ll_to_ph(ll);
	if (!ph)
		return (ll_clear(&ll.head));


	start = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(start, NULL);
	ph->start = start;



	pthread_mutex_lock(start);
	philos = make_philos(ph);
	if (!philos)
		return (3);
	pthread_mutex_unlock(start);


	// monitor = make_monitor(philos);			//TODO: if no monitor, free previous allocated rsrcs
	pthread_join(*make_monitor(philos), (void *)&exit);



	i = -1;
	while (++i < ph->num_philos)
		pthread_detach(philos[i].tid);
	// if (exit == 0LL)
	// {
	// 	sleep(3);
	// 	release(philos, ph, monitor);
	// }
}

	//ISSUE: ACCESSING PHILOS CAUSES SEGFAULT AFTER PTHREAD_JOIN
	//ISSUE: Value of var philos is changed after pthread_join
	//ISSUE_CLOSED: void **retval of pthread_join() should be ptr to ptr (64-bit). integer 'exit' was 32-bit. so retval overwrites philos that follows 'exit' in memory.

	//TODO: release all resources at exit
	//TODO: if error occured, free previous allocated resources
	//TODO: a philo died, simulation has to be terminated

	//NOTE: printf mutex
	//NOTE: when threads have to be detached? right after created? after all thread created?

	//FIXIT: clustering when num of philo is large
	//FIXIT: printing order
	//FIXIT: large case does not work properly

