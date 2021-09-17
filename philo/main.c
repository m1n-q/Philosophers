/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:05:56 by mishin            #+#    #+#             */
/*   Updated: 2021/09/17 17:15:28 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_ll_meta		ll;
	t_philo_meta	ph;
	t_philo			*philos;
	pthread_t		*monitor;
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
		return (2);
	ll_to_ph(ll, &ph);
	ll_clear(&ll.head);
	philos = make_philos(&ph);
	if (!philos)
		return (3);
	i = -1;
	while (++i < *(ph.num_philos))
		pthread_detach(philos[i].tid);			//NOTE: detach here? (after all threads being created)
	monitor = make_monitor(philos);
	pthread_join(*monitor, (void *)&exit);

	if (exit == 0LL)
	{
		sleep(3);
		release(philos, ph, monitor);
	}
}

	//ISSUE: ACCESSING PHILOS CAUSES SEGFAULT AFTER PTHREAD_JOIN
	//ISSUE: Value of var philos is changed after pthread_join
	//ISSUE_CLOSED: void **retval of pthread_join() should be ptr to ptr (64-bit). integer 'exit' was 32-bit. so retval overwrites philos that follows 'exit' in memory.
