/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/17 23:19:10 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	a;

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	*ph;
	t_philo			*philos;
	pthread_t		*monitor;
	long long		exit;
	int				i;

	pthread_mutex_init(&a, NULL);
	i = 0;
	exit = 1;
	ll.head = NULL;
	ll.size = 0;
	while (++i < argc)
		if (input_to_ll(&ll, argv[i]) == -1)
			return (1);
	if (ll.size != 4 && ll.size != 5)
		return (2);
	ph = ll_to_ph(ll);
	if (!ph)
		return (312);
	ll_clear(&ll.head);
	philos = make_philos(ph);
	if (!philos)
		return (3);
	monitor = make_monitor(philos);			//TODO: if no monitor, free previous allocated rsrcs
	i = -1;
	while (++i < ph->num_philos)
		pthread_detach(philos[i].tid);
	pthread_join(*monitor, (void *)&exit);
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
